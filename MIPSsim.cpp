
/* On my honor,I have neither given nor received unauthorized aid on this assignment */

#include <iostream>
#include<fstream>
#include <queue> 
#include<sstream>
#include<string>
#include<cstring>
#include<list>
#include<vector>
#include<algorithm>


using namespace std;
queue<string> inst_queue;
void Issue2();
void Issue1();
string rdecode();
void asu();
void mlu1();
void mlu2();
void addr();
void store();
void write();
void display();
void displayINM();
void displayINB();
void displayAIB();
void displaySIB();
void displayPRB();
void displayADB();
void displayREB();
void displayRGF();
void displayDAM();

 ofstream outfile("simulation.txt",ios::out);
void display()
{
  static int i=0;
  //outfile<<endl;
  outfile<<"STEP "<< i++<<":"<<endl;
  displayINM();
  displayINB();
  displayAIB();
  displaySIB();
  displayPRB();
  displayADB();
  displayREB();
  displayRGF();
  displayDAM();
  outfile<<endl;
}

class RegisterFile
{ 
     public:
     int val;
     string name="-1";
     int token;
    RegisterFile()
    {

    }
 
    RegisterFile( string namegiven,int value)
    {   
        name = namegiven;
        val = value;
    }
    int getval()
    {
        return val;
    }
    string getname()
    {
        return name;
    }
    int getnum()
    {
      if (!name.compare("R0")) { return 0 ;}
      else if(!name.compare("R1")) { return 1;} 
      else if(!name.compare("R2")) { return 2;}
      else if(!name.compare("R3")) { return 3 ;}
      else if(!name.compare("R4")) { return 4 ;}
      else if(!name.compare("R5")) { return 5 ;}
      else if(!name.compare("R6")) { return 6 ;}
      else if(!name.compare("R7")) { return 7 ;}
      else if(!name.compare("R8")) { return 8;}
      else if(!name.compare("R9")) { return 9;}
      else if(!name.compare("R10")) { return 10;}
      else if(!name.compare("R11")) { return 11;}
      else if(!name.compare("R12")) { return 12;}
      else if(!name.compare("R13")) { return 13;}
      else if(!name.compare("R14")) { return 14;}
      else if(!name.compare("R15")) { return 15 ;}
      else if(!name.compare("R16")) { return 16 ;}
      return -1;
      
    }

};
RegisterFile ASU= RegisterFile();
//RegisterFile REB= RegisterFile();


vector<string> split(const string &s, char delim) {
    stringstream ss(s);
    string item;
    vector<string> tokens;
    while (getline(ss, item, delim)) {
        //cout<<item<<endl;
        tokens.push_back(item);
    }
    return tokens;
}



class InstBuffer
{
    public: 
    string opcode="-1";
    string dest="-1";
    int operand1=-1;
    int operand2=-1;
    int token=-1;


    InstBuffer()
    {

    }
    InstBuffer(string op,string destination,int a,int b)
    {
        opcode =op;
        dest=destination;
        operand1=a;
        operand2=b;         
    }
    

};
InstBuffer INB = InstBuffer();
InstBuffer AIB = InstBuffer();
InstBuffer SIB = InstBuffer();
InstBuffer PRB = InstBuffer();


class AddBuf
{
   public:
    string regname="-1";
    int memaddr;
    int token;

    AddBuf()
    {

    }

};
AddBuf ADB = AddBuf();
class DataMem
{  public:
   int addr=-1;
   int val=-1;
   DataMem()
   {

   }
   DataMem(int address,int value)
   {
    addr = address;
    val  = value;
   }
   int getadd() { return addr ; }
   int getval() { return val; }
   void setval(int num)
   {
      val = num;
    }



};
DataMem DAM[16];
class Instr
{

    public: 
    
    string opcode="-1";
    string op1="-1";
    string op2="-1";
    string dest="-1";

    Instr()
    {

    }
    Instr(string opc, string destination,string src1, string src2)
    {
        opcode=opc;
        op1= src1;
        op2= src2;
        dest=destination;
    }
    

};
Instr INM[16];
vector<RegisterFile> registerobjects;
vector<DataMem> memoryobjects;
//memoryobjects.reserve(16);
list<RegisterFile>REB;


int main()
{   
   //initialize data memory
   // cout<<"Before datamem"<<endl;
    //cout<<"ASU"<<ASU.name<<endl<<ASU.val<<endl;
    ifstream datafile("datamemory.txt",ios::in);
    //inFile.open("new.txt");
    if(!datafile)
    {
        
        cerr<<strerror(errno)<<endl;
    }
    string memoryinfo;
    int i=0;
    while(!datafile.eof())

    {   
       
        getline(datafile,memoryinfo);
        //cout<<memoryinfo<<endl;
        //cout<<memoryinfo.size()<<endl;
        //strip off first and last character
        if(memoryinfo.size()>2)
        {    
          
          //cout<<memoryinfo<<endl;
          memoryinfo=memoryinfo.substr(1,memoryinfo.size()-2);
          //cout<<"Size:"<<memoryinfo.size();
          //cout<<memoryinfo<<endl;
        }

        vector<string> vmem;

        vmem = split(memoryinfo,',');

        //cout<<vmem.at(0);
        //cout<<vmem.at(1);
       
        int memname = stoi(vmem.at(0),nullptr,10);
        
        int memval = stoi(vmem.at(1),nullptr,10);

        DataMem mem = DataMem(memname,memval);
        memoryobjects.push_back(mem);

        
     }   
   
   //cout<<"Before registers"<<endl;
    ifstream inputFile("registers.txt",ios::in);
    
    if(!inputFile)
    {

        cerr<< "Couldnt open"<<endl;
        cerr<<strerror(errno)<<endl;
    }
    string registerinfo;
    int k=0;
    while(!inputFile.eof())
    {
      k++;
        //cout<<"Before getline k";
        getline(inputFile,registerinfo);
        //cout<<registerinfo<<endl;
        //strip off first and last character
        if(registerinfo.size()>2)
        {    
          //cout<<registerinfo<<endl;
          registerinfo=registerinfo.substr(1,registerinfo.size()-2);
          //cout<<registerinfo<<endl;
        }

        vector<string> v1;

        v1 = split(registerinfo,',');

        //cout<<v1.at(0);
        //cout<<v1.at(1);

        string regname = v1.at(0);
        
        
        int regval = stoi(v1.at(1),nullptr,10);
    
        RegisterFile reg = RegisterFile(regname,regval);
        //cout<<reg.name<<endl;
        //cout<<reg.val<<endl;
        //cout<<"Before pushback"<<k; 
        registerobjects.push_back(reg);
        //cout<<"After pushback"<<k;
        
    }
   //cout<<"Before close"<<endl;
    inputFile.close(); 

   //cout<<"Before instructions"<<endl;
    //open file and read instruction
    ifstream inFile("instructions.txt",ios::in);
    //inFile.open("new.txt");
    if(!inFile)
    {

        cerr<< "Couldnt open"<<endl;
        cerr<<strerror(errno)<<endl;
    }
    string instruction;

    while(!inFile.eof())
    {
        getline(inFile,instruction);
        //cout<<instruction<<endl;
        //strip off first and last character
        if(instruction.size()>2)
        {    
          instruction=instruction.substr(1,instruction.size()-2);
          //cout<<instruction<<endl;
        }

        //add all instructions to a queue 
        inst_queue.push(instruction);
        //cout<< "Now Queue size is"<< inst_queue.size();
    }

    
  /* for (std::vector<RegisterFile>::iterator it = registerobjects.begin() ; it != registerobjects.end(); ++it)
       {
         cout<< "Register value at "<<it->name<<"is"<<it->val<<endl;
       }
    for (std::vector<DataMem>::iterator itm = memoryobjects.begin() ; itm != memoryobjects.end(); ++itm)
       {
         cout<< "Datamemory value at "<<itm->addr<<"is"<<itm->val<<endl;
       }
*/
    inFile.close();

   
   
   int flag_stop=0;
   display();

  

   
   //while(!flag_stop)
   while(REB.size()>0||PRB.opcode.compare("-1")||AIB.opcode.compare("-1")||ADB.regname.compare("-1")||SIB.opcode.compare("-1")||INB.opcode.compare("-1")||inst_queue.size()>0)
   {  
      
      string opcode="-1";
    
      
      if(REB.size()>0)
      {
        write();
      }
     
      if(PRB.opcode.compare("-1"))
      {
        mlu2();
      }

     
      if(AIB.opcode.compare("-1"))
      {
        if(!AIB.opcode.compare("MUL"))
        {
           mlu1();
        }
      else
        {
          asu();
        }
      }
      
     
      if(ADB.regname.compare("-1"))
      {
        store();
      }
 
      
       if(SIB.opcode.compare("-1"))
      {
        addr();
      }

      
      if(INB.opcode.compare("-1"))
      {
        if(!INB.opcode.compare("ST"))
        {
           Issue2();
        }
      else
        {
          Issue1();
        }
      }

    
     if(inst_queue.size()>0)
      {
        opcode=rdecode();
      }
     
     display();
       
       if(inst_queue.size()==0)
       {
          flag_stop=1;

       }



   } 

    outfile.close();
    return 0;
}

string rdecode()
 {  
    if(inst_queue.size()>0)
   { //InstBuffer newbuf = InstBuffer(NULL,NULL,0,0);
    string newinstr = inst_queue.front();
    //cout<<newinstr;
    inst_queue.pop();
    vector<string> v;
        v = split(newinstr,',');
       Instr instruction = Instr(v.at(0),v.at(1),v.at(2),v.at(3));
       
       INB.opcode=instruction.opcode;
       //cout<<"INB:"<<INB.opcode;
       INB.dest =instruction.dest;

       if(INB.opcode.compare("ST")==0)
       {

         for (std::vector<RegisterFile>::iterator it = registerobjects.begin() ; it != registerobjects.end(); ++it)
       {
            if(instruction.op1.compare(it->name)==0)
            {
                  INB.operand1=it->val;
                  break;
               
            }
       }

            INB.operand2 =stoi(v.at(3));
            //cout<<"inbop2"<<INB.operand2;

       }

       else
       {
       for (std::vector<RegisterFile>::iterator it = registerobjects.begin() ; it != registerobjects.end(); ++it)
       {
            if(instruction.op1.compare(it->name)==0)
            {
                  INB.operand1=it->val;
                  break;
               
            }
       }
      
       for (std::vector<RegisterFile>::iterator it = registerobjects.begin() ; it != registerobjects.end(); ++it)
       {
            if(instruction.op2.compare(it->name)==0)
            {
                  INB.operand2=it->val;
                  break;
               
            }
       }
     }
    //cout<<endl;

    INB.token=1;
    return instruction.opcode;
    //cout<< "op1 is"<<INB.operand1<<endl<<"op2 is"<<INB.operand2<<endl;

   }
   else
   {
     return 0;
   }
 }

   void Issue2()
   {  //cout<<"In issue2:"<<INB.opcode<<endl;
       if(INB.opcode.compare("-1"))
       {
          if(!INB.opcode.compare("ST"))
          {
            SIB.opcode = INB.opcode;
            SIB.dest   = INB.dest;
            SIB.operand1 = INB.operand1;
            SIB.operand2 = INB.operand2;
            //cout<<SIB.opcode<<endl;
            //cout<<SIB.dest<<endl;
            //cout<<SIB.operand1<<endl;
            //cout<<SIB.operand2<<endl;
            INB.opcode="-1";
            INB.dest ="-1";
            INB.operand1=0;
            INB.operand2=0;
         }
         else
         {
           cout<<"Not ST"<<endl;
           
         }

       INB.token=0;
       SIB.token=1;
          
       }
       else
       {
         cout<<"Nothing in INB";
       }
       

   }

   void Issue1()
   {
     //cout<<"In issue2:"<<INB.opcode<<endl;
       if(INB.opcode.compare("-1"))
       {
          if(INB.opcode.compare("ST"))
          {
            AIB.opcode = INB.opcode;
            AIB.dest   = INB.dest;
            AIB.operand1 = INB.operand1;
            AIB.operand2 = INB.operand2;
            //cout<<AIB.opcode<<endl;
            //cout<<AIB.dest<<endl;
            //cout<<AIB.operand1<<endl;
            //cout<<AIB.operand2<<endl;
            INB.opcode="-1";
            INB.dest ="-1";
            INB.operand1=0;
            INB.operand2=0;
         }
         else
         {
           //cout<<"ST"<<endl;
           
         }

       INB.token=0;
       AIB.token=1;
          
       }
       else
       {
         cout<<"Nothing in INB";
       }

       

   }
   void asu()
   {
    if(AIB.opcode.compare("-1"))
    {
      RegisterFile temp = RegisterFile();
      if(!AIB.opcode.compare("ADD"))
      {
          
          temp.name = AIB.dest;
          temp.val  = AIB.operand1+AIB.operand2;
          REB.push_back(temp);
          AIB.opcode="-1";
          AIB.dest  ="-1";
          AIB.operand1=0;
          AIB.operand2=0;
          //cout<<temp.name<<endl;
          //cout<<temp.val<<endl;
      }
      else if(!AIB.opcode.compare("SUB"))
      {
          temp.name = AIB.dest;
          temp.val  = AIB.operand1-AIB.operand2;
          REB.push_back(temp);
          AIB.opcode="-1";
          AIB.dest  ="-1";
          AIB.operand1=0;
          AIB.operand2=0;
          //cout<<temp.name<<endl;
          //cout<<temp.val<<endl;
      }
    
    AIB.token=0;
    }
    else
    {
      //cout<<"Nothing in AIB"<<endl;
    }

   }
   void mlu1()
   {
      if(AIB.opcode.compare("-1"))
    {
      if(!AIB.opcode.compare("MUL"))
      {
          PRB.opcode=AIB.opcode;
          PRB.dest=AIB.dest;
          PRB.operand1=AIB.operand1;
          PRB.operand2=AIB.operand2;
          //cout<<PRB.opcode<<endl;
          //cout<<PRB.dest<<endl;
          //cout<<PRB.operand1<<endl;
          //cout<<PRB.operand2<<endl;
          AIB.opcode="-1";
          AIB.dest="-1";
          AIB.operand1=0;
          AIB.operand2=0;
          
      }

      PRB.token=1;
      AIB.token=0;
      
    }
    else
    {
      //cout<<"Nothing in AIB"<<endl;
    }



   }
   void mlu2()
   {
      if(PRB.opcode.compare("-1"))
    {
      RegisterFile temp = RegisterFile();
      if(!PRB.opcode.compare("MUL"))
      {
          temp.name = PRB.dest;
          temp.val  = PRB.operand1 * PRB.operand2;
          REB.push_back(temp);
          PRB.opcode="-1";
          PRB.dest  ="-1";
          PRB.operand1=0;
          PRB.operand2=0;

          //cout<<temp.name<<endl;
          //cout<<temp.val<<endl;
          PRB.token=0;
          
      }
      
    }
    else
    {
      //cout<<"Nothing in PRB"<<endl;
    }

   }
   void addr()
   {
      if(SIB.opcode.compare("-1"))
      {
        ADB.regname = SIB.dest;
        ADB.memaddr = SIB.operand1+SIB.operand2;
        SIB.opcode  ="-1";
        SIB.dest    ="-1";
        SIB.operand2=0;
        SIB.operand1=0;
        SIB.token=0;
        ADB.token=1;
        //cout<<ADB.regname<<endl;
        //<<ADB.memaddr<<endl;
      }
      else
      {
        //cout<<"Nothing in SIB"<<endl;
      }
      
   }
   void store()
   {
     if(ADB.regname.compare("-1"))
     {
       int towrite;
      for (std::vector<RegisterFile>::iterator it = registerobjects.begin() ; it != registerobjects.end(); ++it) 
      {
          if(it->name.compare(ADB.regname)==0)
          {
            towrite = it->val;
            //cout<<"To write"<<towrite;
            break;
          }
      } 
      int flag_found=0;
      for (std::vector<DataMem>::iterator itm = memoryobjects.begin() ; itm != memoryobjects.end(); ++itm)
      {
          if(itm->addr==ADB.memaddr)
          {
             itm->val=towrite;
             flag_found=1;
             break;
          }

      }
      if (!flag_found)
      {
         memoryobjects.push_back(DataMem(ADB.memaddr,towrite));

      }
      ADB.token=0;
      ADB.regname="-1";
     }
     else
     {
       // cout<<"Nothing in ADB"<<endl;
     }

   }
   void write()
   {
      RegisterFile newobj = RegisterFile();
      newobj=REB.front();
      REB.pop_front();
      //cout<<"First:"<<newobj.name<<endl;
      //cout<<"Second:"<<newobj.val<<endl;
     
       int flag_found=0;
      for (std::vector<RegisterFile>::iterator it = registerobjects.begin() ; it != registerobjects.end(); ++it) 
      {
          if(it->name.compare(newobj.name)==0)
          {
            it->val=newobj.val;
            flag_found=1;
            //cout<<"Wrote"<<newobj.val;
            break;
          }
      } 
      
      if (!flag_found)
      {
         registerobjects.push_back(newobj);
         

      }
    
                  

   }
bool cmd(const DataMem obj1 , const DataMem obj2)
{
   return obj1.addr<obj2.addr;
}

void displayDAM()
{
   //cout<<endl;
  sort(memoryobjects.begin(), memoryobjects.end(), cmd);
  //for (std::vector<DataMem>::iterator it = memoryobjects.begin() ; it != memoryobjects.end(); ++it){ cout<<"<"<<it->addr<<","<<it->val<<">"<<endl;}

   outfile<<endl<<"DAM:";

  // int  i=0;
  // for(i=0;i<16;i++)
  //{
    for (std::vector<DataMem>::iterator it = memoryobjects.begin() ; it != memoryobjects.end(); ++it)
       {
         
         
          //if(it->addr==i)
          //{
            if(it!=memoryobjects.end()-1)
           {   
             outfile<< "<"<<it->addr<<","<<it->val<<">"<<","; 
           }
           else
           {
            outfile<< "<"<<it->addr<<","<<it->val<<">"; 
           }
           
          //} 

       }
  //}
  outfile<<endl;

}
void displayPRB()
{
  outfile<<endl;
  outfile<<"PRB:";
  if(PRB.opcode.compare("-1"))
  {
    outfile<<"<"<<PRB.opcode<<","<<PRB.dest<<","<<PRB.operand1<<","<<PRB.operand2<<">";
  }

}

void displayREB()
{
  outfile<<endl;
  outfile<<"REB:";
  if(!REB.empty())
  {
  for (std::list<RegisterFile>::iterator it=REB.begin(); it != REB.end(); ++it)
 {   
  
  if ((it != REB.end()) && (next(it) == REB.end()))
  {
    outfile<<"<"<<it->name<<","<<it->val<<">";
  }
  else
  {
     outfile<<"<"<<it->name<<","<<it->val<<">"<<",";
  }
 }
}
}

void displayADB()
{
   outfile<<endl;
   outfile<<"ADB:";
   if(ADB.regname.compare("-1"))
   {
     outfile<<"<"<<ADB.regname<<","<<ADB.memaddr<<">";
   }

}

void displaySIB()
{
  outfile<<endl;
  outfile<<"SIB:";
  if(SIB.opcode.compare("-1"))
  {
    outfile<<"<"<<SIB.opcode<<","<<SIB.dest<<","<<SIB.operand1<<","<<SIB.operand2<<">";
  }
  


}

void displayINM()
{
  outfile<<"INM:";
  queue<string> tempqueue= inst_queue;
  while (!tempqueue.empty())
  { 
    //cout<<tempqueue.front();
    if(tempqueue.size()==1)
    {
      outfile <<"<"<<tempqueue.front()<<">";
    }
    else
    { outfile <<"<"<<tempqueue.front()<<">"<< ","; }
    tempqueue.pop();
  }
  
}
void displayINB()
{
  outfile<<endl;
  outfile<<"INB:";
  if(INB.opcode.compare("-1"))
   { outfile<<"<"<<INB.opcode<<","<<INB.dest<<","<<INB.operand1<<","<<INB.operand2<<">"; }
}
void displayAIB()
{
  outfile<<endl;
  outfile<<"AIB:";
  if(AIB.opcode.compare("-1"))
  {
    outfile<<"<"<<AIB.opcode<<","<<AIB.dest<<","<<AIB.operand1<<","<<AIB.operand2<<">";
  }
  
  
}
bool cmdreg(RegisterFile obj1 ,RegisterFile obj2)
{
   return obj1.getnum()<obj2.getnum();
}

   void displayRGF()
{ 
   outfile<<endl<<"RGF:";
   int  i=0;
  //registerobjects.sort();
  //for(i=0;i<16;i++)
  //{
   sort(registerobjects.begin(), registerobjects.end(),cmdreg);
    for (std::vector<RegisterFile>::iterator it = registerobjects.begin() ; it != registerobjects.end(); ++it)
       {

        
        
         //if(it->getnum()==i)
         // {
            //if(i!=15)  
            if(it!=registerobjects.end()-1)
            {outfile<< "<"<<it->name<<","<<it->val<<">"<<","; }
            else
             {outfile<< "<"<<it->name<<","<<it->val<<">"; }
          //}

        }
       

       }
  
