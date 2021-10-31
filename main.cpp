#include<iostream>
#include<fstream>
#include<cctype>
#include<iomanip>
#include <ctime>
#include <cstring>  
#include <sstream> 

using namespace std;

class Bank
{
	int account_no_; //Variable for account number
	char name_[50]; //Variable for Name
	int balance_; //Variable for Name
	char type; //Variable for type of account
	char address_[100]; //Variable for address
public:
	void create_account();	//Function to get the account holder information
	void show_account() const;	//Function to display all the account holder information
	void deposit(int);	//function to accept amount and add to balance amount
	void withdraw(int);	//function to accept amount and subtract from balance amount
	void report() const;	//function to show data in tabular format
	int ret_acc_no() const;	//function to return account number
	int ret_balance() const;	//function to return balance amount
	char ret_type() const;	//function to return type of account
	void show_name() const; //function to return the name
	void show_address() const; // function to return the address
    void show_balance() const; // function to return the balance
    
};

class Transaction
{
    
    
	int account_no_;
    int draw_;
    int deposit_;
    int day_;
    int month_;
    int year_;
public:
        void draw_withdraw(int,int,int);
        void trans_report() const;//function for transaction
        void trans_compute();
		int get_transaction(int);
		void last_entry();
		int get_number(); //to get the account number
};



//Function to create a account
void Bank::create_account()
{
	cout<<"\nEnter The account No. :";
	cin>>account_no_;
	cout<<"\n\nEnter The Name of The account Holder : ";
	cin.ignore();
	cin.getline(name_,50);
	cout<<"\nEnter Type of The account (C/S) : ";
	cin>>type;
	type=toupper(type);
	cout<<"\nEnter The Initial amount: ";
	cin>>balance_;
	cout<<"\nEnter the Address of the Account Holder : ";
	cin>>address_;
	

	Transaction t;
	ofstream trans;
	trans.open("transaction_",ios::binary|ios::app);
	t.draw_withdraw(account_no_,balance_, 1);
	trans.write((char *)&  t, sizeof(Transaction));

	cout<<"\n\n\nAccount Created..";
}

void Bank::show_account() const
{
	cout<<"\nAccount No. : "<<account_no_;
	cout<<"\nAccount Holder Name : ";
	cout<<name_;
	cout<<"\nType of Account : "<<type;
	cout<<"\nBalance amount : "<<balance_;
  cout<<"\nAddress : "<<address_;
}

//To display all the account holder information
void Bank::report() const
{
	cout<<account_no_<<"\t\t"<<name_<<"\t\t\t"<<address_<<"\t\t"<<type<<"\t\t"<<balance_<<endl;
}

//Updating the balance while depositing
void Bank::deposit(int x)
{
	balance_+=x;
}

//Updating the balance while withdrawing	
void Bank::withdraw(int x)
{
	balance_-=x;
}

//To get the account number
int Bank::ret_acc_no() const
{
	return account_no_;
}

//To get the balance
int Bank::ret_balance() const
{
	return balance_;
}

//To get the type of the account2

char Bank::ret_type() const
{
	return type;
}

//To print the name(Retrieve Name)
void Bank::show_name() const
{
	cout<<"\nAccount Number : "<<account_no_;
	cout<<"\nAccount Holder : "<<name_;
}

//To print the address(Retrieve Address)
void Bank::show_address() const
{
	cout<<"\nAccount Number : "<<account_no_;
	cout<<"\nAccount Holder Address : "<<address_;
}

//To print the balance(Retrieve Balance)
void Bank::show_balance() const
{
	cout<<"\nAccount Number : "<<account_no_;
	cout<<"\nAccount Balance : "<<balance_;
}

//To get the account number
int Transaction::get_number()
{
	return account_no_;
}

//Transaction initializer
void Transaction::draw_withdraw(int account_no, int deposit, int draw)
{
  char ch;     
cout<<"\nDo you want to take the date automatically? if yes press 'y' else press 'n' : ";
cin>>ch;
if(ch=='y')
{
//****************************************//
// Commnet below to activate the automatic date storage
//********************************************//
time_t now = time(0);

 tm *ltm = localtime(&now);    

year_= 1900 + ltm->tm_year;
   month_ = 1 + ltm->tm_mon;
   day_ = ltm->tm_mday;
}
else {
//****************************************//
// Commnet below to disable the automatic date storage
//********************************************//
	string date_;
    cout<<"Enter the date in the format (dd/mm/yyyy) : ";
    cin>>date_;
	
				string T;
                string a[3];
                int b[3];
                 int i=0;
                 
                 stringstream X(date_);
                 while (getline(X, T, '/')) { 
                    a[i]=T;
                    i++;
                }
                            
                            
                 for(int i=0;i<3;i++)
                {
                    b[i]=stoi( a[i] );
                                
                }
                
              
               year_ =b[2];
               month_ =b[1];
              day_ = b[0];

}
    account_no_=account_no;
    deposit_=deposit;
    draw_=draw;
   
}

//Transaction Output
void Transaction::trans_report() const
{

    cout<<day_<<"/"<<month_<<"/"<<year_;
     cout<<setw(10)<<" ";   
	cout<<account_no_;
    cout<<setw(10)<<" ";

    if(deposit_!=0)
    {
        cout<<deposit_;
    }
    else{
        cout<<"-";
    }
    cout<<setw(10)<<" ";
    if(draw_!=0)
    {
    cout<<draw_;
    }
    else{
        cout<<"-";
    }
    
    cout<<endl;
}

// A date has day 'd', month 'm' and year 'y'
struct Date {
    int d, m, y;
};
 
 const int monthDays[12]
    = { 31, 28, 31, 30, 31, 30,
       31, 31, 30, 31, 30, 31 };
  int countLeapYears(Date d)
{
    int years = d.y;
 
    // Check if the current year needs to be
    //  considered for the count of leap years
    // or not
    if (d.m <= 2)
        years--;
 
    // An year is a leap year if it
    // is a multiple of 4,
    // multiple of 400 and not a
     // multiple of 100.
    return years / 4
           - years / 100
           + years / 400;
}

int getDifference(Date dt1, Date dt2)
{
    // COUNT TOTAL NUMBER OF DAYS
    // BEFORE FIRST DATE 'dt1'
 
    // initialize count using years and day
    long int n1 = dt1.y * 365 + dt1.d;
 
    // Add days for months in given date
    for (int i = 0; i < dt1.m - 1; i++)
        n1 += monthDays[i];
 
    // Since every leap year is of 366 days,
    // Add a day for every leap year
    n1 += countLeapYears(dt1);
 
    // SIMILARLY, COUNT TOTAL NUMBER OF
    // DAYS BEFORE 'dt2'
 
    long int n2 = dt2.y * 365 + dt2.d;
    for (int i = 0; i < dt2.m - 1; i++)
        n2 += monthDays[i];
    n2 += countLeapYears(dt2);
 
    // return difference between two counts
    return (n2 - n1);
}

int Transaction::get_transaction(int num)
{
	int day1,month1,year1;
	
   time_t now = time(0);
   tm *ltm = localtime(&now);
   year1=1900 + ltm->tm_year;
   month1= 1 + ltm->tm_mon;
   day1 = ltm->tm_mday ;


	 int max_day=day1, max_month=month1, max_year=year1;
	
	Transaction t;
	ifstream trans;
	trans.open("transaction_",ios::binary);


	while(trans.read((char *)&  t, sizeof(Transaction)))
	{
		if(num==t.account_no_&&t.draw_>0)
		{
			max_day=t.day_;
			max_month=t.month_;
			max_year=t.year_;
		}
	}

    Date dt1 = { max_day, max_month, max_year };
    Date dt2 = { day1, month1, year1};

         if((getDifference(dt1, dt2)>30))
         {
            return num;
         } else	return 0;

	trans.close();
}

void Transaction::trans_compute()
{
	int num,acc_no;
	Bank b;
	ifstream inFile;
	inFile.open("account_",ios::binary);

	while(inFile.read((char *)&  b, sizeof(Bank)))
	{
		num=b.ret_acc_no();
		acc_no=get_transaction(num);

		if(acc_no!=0)
		{
		cout<<"\nThe interest for the account number "<<num<<" for previous month (6%  interest ) is :"<<b.ret_balance()*0.06<<endl;
		}

	}
		inFile.close();	
   
}

void Transaction::last_entry()
{
	Transaction t;
	ifstream trans;
	int acc;
	trans.open("transaction_",ios::binary);


	while(trans.read((char *)&  t, sizeof(Transaction)))
	{
		acc=t.account_no_;
	}

	cout<<"Last entry of the Account Holder is "<<acc;
	trans.close();
}


//***************************************************************
//    	function declaration
//****************************************************************
void write_account();	//function to write record in binary file
void display_all();		//function to display all account details
void deposit_withdraw(int, int); // function to desposit/withdraw amount for given account
void delete_account(int); //function to delete the account holder
void exist(int); //function to check whether the account number is exist
void display_sp(int,int); //function to retrieve the name, address and balance
void display_all_transaction(); //Display all transaction
void compute(); //To compute the ineterest
void display_last(); //To display the last
int main()
{
	int ch;
	int num;
	do
	{
		
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. New Account";
        cout<<"\n\n\t02. All Account Holder List";
        cout<<"\n\n\t03. Delete An Account";
        cout<<"\n\n\t04. Deposit Amount";
        cout<<"\n\n\t05. Withdraw amount";
        cout<<"\n\n\t06. Find Account";
        cout<<"\n\n\t07. Retrieve Name";
		cout<<"\n\n\t08. Retrieve Address";
        cout<<"\n\n\t09. Balace Enquiry";
		cout<<"\n\n\t10. Account Holder Information";
        cout<<"\n\n\t11. Transaction Record of Particular Account Holder"; 
		cout<<"\n\n\t12. Interest Of All The Account Holder";
		cout<<"\n\n\t13. Account Number Of The Last Entry";
        cout<<"\n\n\t >>";
		cin>>ch;
	
		switch(ch)
		{
		case 1:
			write_account();
			break;
        case 2:
			display_all();
			break;
	    case 3:
		 	cout<<"\n\n\tEnter The account No. : "; cin>>num;
		 	delete_account(num);
		 	break;	
	

        case 4: 
		    cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 1);
			break;

        case 5:
			cout<<"\n\n\tEnter The account No. : "; cin>>num;
			deposit_withdraw(num, 2);
			break;
        
        case 6:
				cout<<"\n\n\tEnter The account No. : "; cin>>num;
		 		exist(num);
		 		break;
        case 7:
				cout<<"\n\n\tEnter The account No. : "; cin>>num;
				display_sp(num,1);//For retrieving the name
				break;

        case 8: 
			    cout<<"\n\n\tEnter The account No. : "; cin>>num;
			    display_sp(num,2);//For retrieving the address
			    break;  

        case 9:  
			    cout<<"\n\n\tEnter The account No. : "; cin>>num;
			    display_sp(num,3);
			    break;       
        case 10:
                cout<<"\n\n\tEnter The account No. : "; cin>>num;
			    display_sp(num,4);
			    break;

		case 11:
		 		display_all_transaction();
		 		break;
		case 12: 
                compute();
                break;
		case 13:
				display_last();
				break;
		
		 default :cout<<"\a";
		}

		cin.ignore();

        cout<<"\nPress Enter to Continue..";
		cin.get();
	}while(ch!=14);
    
	return 0;
}
//***************************************************************
//    	function to write in file while account creation
//****************************************************************

void write_account()
{
	Bank b;
	ofstream outFile;
	outFile.open("account_",ios::binary|ios::app);
	b.create_account();
	outFile.write((char *)&  b, sizeof(Bank));
    cout<<"\n";
	outFile.close();

	
}

//***************************************************************
//    	function to display all accounts deposit list
//****************************************************************

void display_all()
{
	Bank b;
	ifstream inFile;
	inFile.open("account_",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout<<"====================================================\n";
	cout<<"A/c no.   NAME    Address    Type  Balance\n";
	cout<<"====================================================\n";
	while(inFile.read((char *)&  b, sizeof(Bank)))
	{
		b.report();
	}
	inFile.close();
   
}

//***************************************************************
//    	function to delete record of file
//****************************************************************


void delete_account(int n)
{
	Bank b;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account_",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *)&  b, sizeof(Bank)))
	{
		if(b.ret_acc_no()!=n)
		{
			outFile.write((char *)&  b, sizeof(Bank));
		}
	}
	inFile.close();
	outFile.close();
	remove("account_");
	rename("Temp","account_");
	cout<<"\n\n\tRecord Deleted ..";
}


//***************************************************************
//    	function to deposit and withdraw amounts
//****************************************************************

void deposit_withdraw(int n, int option)
{
	int amt;
	bool found=false;
	Bank b;
    
    Transaction t;

	fstream File;

    ofstream trans;

    
	File.open("account_", ios::binary|ios::in|ios::out);

    trans.open("transaction_",ios::binary|ios::app);
	if(!File)
	{
		cout<<"File could not be open !! ";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read((char *)&  b, sizeof(Bank));
		if(b.ret_acc_no()==n)
		{
			b.show_account();
			if(option==1)
			{
				cout<<"\n\n\tTO DEPOSITE AMOUNT ";
				cout<<"\n\nEnter The amount to be deposited : ";
				cin>>amt;
				b.deposit(amt);

                t.draw_withdraw(b.ret_acc_no(), amt, 0);
			};
			if(option==2)
			{
				cout<<"\n\n\tTO WITHDRAW AMOUNT ";
				cout<<"\n\nEnter The amount to be withdraw : ";
				cin>>amt;
				int bal=b.ret_balance()-amt;
				if((bal<500 && b.ret_type()=='S') || (bal<1000 && b.ret_type()=='C'))
					cout<<"Insufficience balance";
				else
					b.withdraw(amt);
                    
                    t.draw_withdraw(b.ret_acc_no(),0, amt);
			}

		
			//trans.write((char *)&  t, sizeof(Transaction));

			int pos=(-1)*static_cast<int>(sizeof(b));
			File.seekp(pos,ios::cur);
			File.write((char *)&  b, sizeof(Bank));
            
            trans.write((char *)&  t, sizeof(Transaction));
            
			cout<<"\n\n\t Record Updated";

			found=true;
			
	       }
         }
	File.close();
	
    trans.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	
}

// ***************************************************************
//    	function to check whether the account exist
// ****************************************************************

void exist(int n)
{
	Bank b;
	bool flag=false;
	ifstream inFile;
	inFile.open("account_",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	

    	while(inFile.read((char *)&  b, sizeof(Bank)))
	{
		if(b.ret_acc_no()==n)
		{
			cout<<"\nAccount number exist\n";
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

// ***************************************************************
//    	function to retrieve the name, addrees and balance
// ****************************************************************
void display_sp(int n, int m)
{
	Bank b;
	bool flag=false;
	ifstream inFile;
	inFile.open("account_",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\nBALANCE DETAILS\n";

    	while(inFile.read((char *)&  b, sizeof(Bank)))
	{
		if(b.ret_acc_no()==n)
		{
			if(m==1)
			{
			b.show_name();
			}

			if(m==2)
			{
				b.show_address();
			}

			if(m==3)
			{
				b.show_balance();
			}
            if(m==4)
			{
				b.show_account();
			}
			flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nAccount number does not exist";
}

//***************************************************************
//    	function to display all transaction
//****************************************************************

void display_all_transaction()
{
	int num;
	cout<<"Enter the account number : ";
	cin>>num;
	Transaction b;
	ifstream inFile;
	inFile.open("transaction_",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	cout<<"\n\n\t\tACCOUNT TRANSACTION LIST\n\n";
	cout<<"====================================================\n";
	cout<<"Date             A/c no.     Deposit           Withdraw\n";
	cout<<"====================================================\n";
	while(inFile.read((char *)&  b, sizeof(Transaction)))
	{
		if(b.get_number()==num)
		{
			b.trans_report();
		}

		
	}
	inFile.close();
   
}

void compute()
{
    Transaction t;
	t.trans_compute();  
}

//***************************************************************
//    	function to display the last entry
//****************************************************************

void display_last()
{
	Transaction t;
	t.last_entry();
}
