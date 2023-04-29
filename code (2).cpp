#include <iostream>
#include <vector>
using namespace std;

class Student;
class StudentBuilder;

class StudentBuilder
{
    int rollNo;
    int age;
    unsigned long long MNo;
    string name;
    
    protected:
    vector<string> subjects;
    
    public:
    StudentBuilder* setRollNo(int rollNo) {
        this->rollNo = rollNo;
    }
    
    StudentBuilder* setAge(int age) {
        this->age = age;
    }
    
    StudentBuilder* setName(string name) {
        this->name = name;
    }
    
    StudentBuilder* setMobileNo(unsigned long long MNo) {
        this->MNo = MNo;
    }
    
    virtual StudentBuilder* setSubjects() = 0;
    
    int getRollNo() {
        return rollNo;
    }
    
    int getAge() {
        return age;
    }
    
    string getName() {
        return name;
    }
    
    unsigned long long getMobileNo() {
        return MNo;
    }
    
    vector<string> getSubjects() {
        return subjects;
    }
    
    Student* buildStudent(); 
};

class Student 
{
    int rollNo;
    int age;
    string name;
    vector<string> subject;
    unsigned long long MNo;
    
    public:
    Student(StudentBuilder *ptr):
    rollNo{ptr->getRollNo()},
    age{ptr->getAge()},
    name{ptr->getName()},
    subject{ptr->getSubjects()},
    MNo{ptr->getMobileNo()}
    {}
    
    string showData()
    {
        to_string(rollNo) + to_string(age) + name +  subject[0] + " " + subject[1] + " " +
        subject[2] + to_string(MNo);
    }
};

Student* StudentBuilder::buildStudent() {
    return (new Student(this));
}

class ScienceStudent : public StudentBuilder
{
    public:
    StudentBuilder* setSubjects() override {
        vector<string> subjects{"Phy", "Che", "Math"};
        this->subjects = subjects;
        return this;
    }
};

class ArtsStudent : public StudentBuilder
{
    public:
    StudentBuilder* setSubjects() override {
        vector<string> subjects{"His", "Geo", "Eco"};
        this->subjects = subjects;
        return this;
    }
};

class Director
{
    StudentBuilder *ptr;
    string streamName;
    
    public:
    Director(StudentBuilder *ptrSb, string streamNamePassed) : 
    ptr{ptrSb},
    streamName{streamNamePassed}
    {}
    
    Student* createStudent() {
        if(streamName == "Sceince")
            return ptr->setRollNo(50)->setName("Anil")->setAge(17)->setSubjects()->
                   setMobileNo(123)->buildStudent();
        else if(streamName == "Arts")
            return ptr->setRollNo(50)->setName("Anil")->setAge(16)->setSubjects()->buildStudent();
        else
            return nullptr;
    }
};

int main() {
	Director *sciDir = new Director(new ScienceStudent, "Sceince");
	Director *artsDir = new Director(new ArtsStudent, "Arts");
	
	Student *sciStud = sciDir->createStudent();
	Student *artsStud = artsDir->createStudent();
	
	cout<<sciStud->showData()<<endl;
	cout<<artsStud->showData()<<endl;
	return 0;
}