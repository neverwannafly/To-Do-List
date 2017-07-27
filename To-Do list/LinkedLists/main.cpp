#include <iostream>
typedef std::ostream s_os;
typedef std::string s_str;
s_str ch = "-> ";

class toDo{
    friend s_os &operator<<(s_os &os, const toDo &t);
    friend class list;
public:
    toDo(s_str task, bool urgent);
private:
    s_str task;
    bool urgent;
    toDo *next, *prev;
};
s_os &operator<<(s_os &os, const toDo &t){
    s_str str;
    t.urgent == true ? str = " - Urgent" : str = " - Not Urgent";
    os << t.task << str << std::endl;
    return os;
}
toDo::toDo(s_str task, bool urgent){
    this->task = task;
    this->urgent = urgent;
    next = NULL;
    prev = NULL;
}

class list{
public:
    list();
    void addToHead(s_str task, bool urgent);
    void addToTail(s_str task, bool urgent);
    void deleteByPriority();
    void printByPriority();
    static int returnSize();
private:
    toDo *head, *tail;
    static int size;
};
int list::size = 0;
list::list(){
    head = NULL;
    tail = NULL;
}
void list::addToHead(s_str task, bool urgent){
    
    toDo *newPtr = new toDo(task, urgent);
    if(head==NULL){
        head = newPtr;
        tail = newPtr;
    }
    else{
        newPtr->next = head;
        head->prev = newPtr;
        head = newPtr;
    }
    ++size;
}
void list::addToTail(s_str task, bool urgent){

    toDo *newPtr = new toDo(task, urgent);
    if(head==NULL){
        head = newPtr;
        tail = newPtr;
    }
    else{
        newPtr->prev = tail;
        tail->next = newPtr;
        tail = newPtr;
    }
    ++size;
}
void list::deleteByPriority(){

    if(head==NULL)
        std::cout << "To-Do list already empty" << std::endl;
    else if(head==tail){
        head = NULL;
        tail = NULL;
    }else{
        toDo *temp;
        temp = head->next;
        temp->prev = NULL;
        head->next = NULL;
        head = temp;
    }
    --size;
}
void list::printByPriority(){
    
    toDo *temp;
    temp = head;
    while(temp!=NULL){
        std::cout << ch <<*temp;
        temp = temp->next;
    }
}
int list::returnSize(){
    return size;
}

int main(){

    s_str task;
    bool urgent, cond = true;
    list *cl1 = new list();
    int choice;
    
    std::cout << "\t\tTo-Do LIST\n\n";
    std::cout << "1. Start by adding a task" << std::endl;
    std::cout << "2. Exit" << std::endl;
    std::cin >> choice;
    
    if(choice==1){
        std::cout << "Specify your task : ";
        std::cin.ignore();
        std::getline(std::cin, task);
        std::cout << "Is your task urgent ? (1/0) : " << std::endl;
        std::cin.ignore(0);
        std::cin >> urgent;
        
        if(urgent==true)
            cl1->addToHead(task, urgent);
        else
            cl1->addToTail(task, urgent);
        do{
            std::cout << "You have " << cl1->returnSize() << " task/s left!" << std::endl;
            cl1->printByPriority();
            std::cout << "1. Add more tasks." << std::endl;
            std::cout << "2. Finished TASK#1!!!!!:'D" << std::endl;
            std::cout << "3. Exit" << std::endl;
            std::cin >> choice;
            switch(choice){
                case 1:
                    std::cout << "Specify your task : ";
                    std::cin.ignore();
                    std::getline(std::cin, task);
                    std::cout << "Is your task urgent ? (1/0) : " ;
                    std::cin.ignore(0);
                    std::cin >> urgent;
                    
                    if(urgent==true)
                        cl1->addToHead(task, urgent);
                    else
                        cl1->addToTail(task, urgent);
                    break;
                case 2:
                    cl1->deleteByPriority();
                    if(cl1->returnSize()==0){
                        std::cout << "Congratulations ! All tasks are completed :') !" << std::endl;
                        cond = false;
                    }
                    break;
                default:
                    cond = false;
                    break;
            }
            
        }while(cond==true);
    }
    
    std::cout << "Thank you for using our App :') !" << std::endl;

    return 0;
}
