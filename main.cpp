#include <iostream>
//author Reem Ehab
using namespace std;
template <class type>
class myList
{
public:
    class Node
    {
        friend class myList;
        type Info;
        Node *next;
        Node *previous;
    public:
        Node()
        {
            previous=next=NULL;
        }
        type getInfo()
        {
            return Info;
        }
    };

private :
    int sizeOfList;
    Node *head,*tail, *dummy;
public:
    class iteratorr
    {
    private :
        friend class myList;
        Node * Current;
    public:

        iteratorr(Node *object)
        {
            Current = object;
        }

        void operator++ (int)
        {
            if (Current->next == NULL)
            {
                cout<<" there is no Next Node"<<endl;
            }
            Current = Current->next;
        }
        void operator-- (int)
        {
            if (Current->previous == NULL)
            {
                cout<<" there is no previous Node "<<endl;
            }
            Current = Current->previous;
        }
        type& operator* ()
        {
            return Current->Info;
        }

        bool operator== (const iteratorr &object)
        {
            if(object.Current == Current)
                return true;
            return false;
        }
        bool operator!= (const iteratorr &object)
        {
            if(object.Current == Current)
                return false;
            return true;
        }

        /// your code for the iterator class here

    };
    myList()  ///default constructor
    {
        dummy = new Node();
        dummy->Info = 0;
        dummy->next = NULL;
        dummy->previous = NULL;
        head = dummy;
        sizeOfList = 0;
    }
    myList(type value, int initial_size) /// Parmetrized constructor for myList
    {
        head = NULL;
        tail= NULL;
        this->sizeOfList=initial_size;
        for(int i=0 ; i<sizeOfList ; i++)
        {
            Node* newNode = new Node();
            if(head==NULL && tail==NULL) ///means that there is no nodes at all
            {
                newNode->Info = value;
                head = newNode;
                tail = newNode;
                head->previous = NULL;
                tail ->previous = NULL;
                dummy = new Node();
                head->next = dummy;
                tail->next = dummy;
                dummy->previous = tail;
                dummy->next = NULL;
            }
            else  ///then there is one node or more
            {
                newNode->Info=value;
                newNode->previous=tail;
                tail->next=newNode;
                tail=newNode;
                tail->next = dummy;
                dummy->previous = tail;
                dummy->next = NULL;
            }
        }

    }

    int getSizeOfList() ///function to return the current size of a list
    {
        return sizeOfList;
    }

    void insertt(type value, iteratorr &position) ///when i give him a position new value is added in this position and the old value is shifted
    {
        Node* newNode = new Node;
        newNode->Info=value;
        if(position.Current==head)
        {
            head->previous=newNode;
            newNode->next=head;
            head = newNode;
            head->previous = NULL;
            sizeOfList++;
        }
        else
        {

            Node *previousNode = position.Current->previous;
            previousNode->next=newNode;
            newNode->previous=previousNode;
            position.Current->previous=newNode;
            newNode->next=position.Current;
            sizeOfList++;
        }

    }
    iteratorr erase(iteratorr position) ///– erases the element specified by the iterator and return an iterator to the next element,
    ///throws exception if position points after the last element.
    {
        try
        {
            if(position.Current==NULL)
            {
                throw "no next element" ;
            }
            else if(position.Current==head)
            {
                Node * after= head->next;
                head=after;
                after->previous=NULL;
                sizeOfList--;
            }
            else
            {
                Node * afterNode = position.Current->next; /// the node after the Node i want to erase
                Node * beforeNode = position.Current->previous; /// the node before the Node i want to erase
                position.Current=NULL;
                beforeNode->next=afterNode;
                afterNode->previous=beforeNode;
                sizeOfList--;
            }
        }
        catch (const char *msg) /// Handle exception
        {
            cout << "Error: " << msg;
        }
    }
    myList<type> & operator = (myList<type> &another_list) ///– overloads the assignment operator to deep copy a list into another list
    ///and return the current list by reference
    {
        Node *current = another_list.head;
        Node *new_node=new Node();
        sizeOfList = another_list.sizeOfList;
        new_node->Info = current->Info;
        new_node->next = dummy;
        new_node->previous = NULL;
        tail = head = new_node;
        dummy->previous = tail;
        dummy->next = NULL;
        current = current->next;
        while (current != another_list.dummy)
        {
            new_node = new Node();
            new_node->Info = current->Info;
            new_node->next = NULL;
            new_node->previous = tail;
            tail->next = new_node;
            tail = new_node;
            current = current->next;
        }
        tail->next = dummy;
        dummy->previous = tail;
        dummy->next = NULL;
        return *this;
    }
    iteratorr begin()
    {
        iteratorr it(head);
        return it.Current;
    }
    iteratorr end()
    {
        iteratorr it(dummy);
        return it.Current;
    }

    void Display()
    {
        Node* newNode = head;
        while (newNode != dummy)
        {
            cout << newNode->Info << " ";
            newNode = newNode->next;
        }
        cout<<" with Size = "<<getSizeOfList()<<endl;
    }
    ~myList()
    {
        Node* current = head;
        iteratorr it= this->begin();
        it++;
        for( ; it != this->end() ; it++ )
        {
            Node* toBeRemoved = current->next;
            delete current;
            current = toBeRemoved;
        }
        head=0;
    }

};

void merge(myList<int>& m1,myList<int> &m2)
{
    ///remove list 1 duplicates
    myList<int>::iteratorr it3 = m1.begin();
    while(it3 != m1.end())
    {
        myList<int>::iteratorr it4 = it3;
        it4++;
        while(it4 != m1.end())
        {
            if (*it3 == *it4)
            {
                m1.erase(it4);
            }
            it4++;
        }
        it3++;
    }
    myList<int>::iteratorr it2 = m2.begin();
    while (it2 != m2.end())
    {
        myList<int>::iteratorr tmp = NULL;
        myList<int>::iteratorr it1 = m1.begin();
        bool ok = true,check = false;
        while(it1 != m1.end())
        {
            if(*it1 == *it2)
            {
                ok = false;
                break;
            }
            else if(*it1 > *it2 && !check)
            {
                tmp = it1;
                check = true;
            }
            it1++;
        }
        if(ok)
        {
            if(tmp == NULL)
            {
                tmp = m1.end();
            }
            m1.insertt(*it2,tmp);
        }
        it2++;
    }
}

int main()
{
    myList<int> list1(11,3);
    myList<int>::iteratorr listIterator1 = list1.begin();
    list1.insertt(4, listIterator1);
    list1.insertt(3, listIterator1);
    list1.insertt(4, listIterator1);
    list1.insertt(4, listIterator1);
    list1.insertt(6, listIterator1);
    list1.insertt(8, listIterator1);
    list1.insertt(10, listIterator1);

    cout<<"_________________________my first List is ________________________________:"<<endl;
    list1.Display();
    myList<int> list2(12,1);
    myList<int>::iteratorr listIterator2 = list2.begin();
    list2.insertt(5,listIterator2);
    list2.insertt(5,listIterator2);
    list2.insertt(7,listIterator2);
    list2.insertt(9,listIterator2);
    cout<<" _______________my second List is_________________________________________:"<<endl;
    list2.Display();
    cout<<" _____________after Merging list1 and list2________________________________:"<<endl;
    merge(list1,list2);
    list1.Display();
    /*myList<int> list3;
    list3 = list1;
    list3.Display();
    list1.Display();
    myList<int>::iteratorr i3 = list3.begin();
    list3.insertt(89,i3);
    list3.Display();
    list1.Display();*/

    return 0;
}
