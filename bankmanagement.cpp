#include<iostream>
#include<windows.h>
#include<fstream>
#include<cctype>
#include<conio.h>
#include<iomanip>
using namespace std;
void gotoxy(short x, short y);
void screen();
void password();
void Main_Menu();
void writeAc();
void dispAc(int);
void modifyAc(int);
void deleteAc(int);
void dispall();
void withdraw(int, int);

class account
{
	int acno;
	char name[50];
	int deposit;
	char type;
public:
	void createAc();
	void showAc() const;
	void modify();
	void dep(int);
	void widr(int);
	void report() const;
	int retAc() const;
	int retdeposit() const;
	char rettype() const;
};

void account::createAc()
{
	gotoxy(32,7);
	cout<<"NEW ACCOUNT";
	gotoxy(32,8);
	cout<<"------------";
	gotoxy(15,10);
	cout<<"Account No. : ";
	gotoxy(46,10);
	cout<<"A/C Holder Name: ";
	gotoxy(15,12);
	cout<<"Type of the Account (C/S) : ";
	gotoxy(46,12);
	cout<<"Initial amount : ";
	gotoxy(28,10);
	cin>>acno;
	gotoxy(62,10);
	cin.ignore();
	cin.getline(name,50);
	gotoxy(42,12);
	cin>>type;
	type=toupper(type);
	gotoxy(62,12);
	cin>>deposit;
	gotoxy(15,14);
	cout<<"Account Created..";
}

void account::showAc() const
{	gotoxy(15,10);
	cout<<"Account No. : "<<acno;
	gotoxy(15,12);
	cout<<"Account Holder Name : "<<name;
	gotoxy(15,14);
	cout<<"Type of Account : "<<type;
	gotoxy(15,16);
	cout<<"Balance amount : "<<deposit;
}


void account::modify()
{
	gotoxy(15,20);
	cout<<"Account No. : "<<acno;
	gotoxy(45,20);
	cout<<"A/C Holder Name : ";
	gotoxy(15,22);
	cout<<"Type of A/C : ";
	gotoxy(45,22);
	cout<<"Balance amount : ";
	gotoxy(63,20);
	cin.ignore();
	cin.getline(name,50);
	gotoxy(29,22);
	cin>>type;
	type=toupper(type);
	gotoxy(62,22);
	cin>>deposit;
}


void account::dep(int x)
{
	deposit+=x;
}

void account::widr(int x)
{
	deposit-=x;
}

void account::report() const
{
	gotoxy(15,13);
	cout<<""<<acno<<setw(10)<<" "<<name<<setw(13)<<" "<<type<<setw(16)<<deposit<<endl;
}

int account::retAc() const
{
	return acno;
}

int account::retdeposit() const
{
	return deposit;
}

char account::rettype() const
{
	return type;
}

void Main_Menu()
{
	char ch;
	int num;
	do
	{
		system("CLS");
		screen();
		gotoxy(31,7);
		cout<<"|| MAIN MENU ||";
		gotoxy(31,8);
		cout<<"---------------";
		gotoxy(20,9);
		cout<<"1. NEW ACCOUNT";
		gotoxy(20,10);
		cout<<"2. DEPOSIT AMOUNT";
		gotoxy(20,11);
		cout<<"3. WITHDRAW AMOUNT";
		gotoxy(20,12);
		cout<<"4. BALANCE ENQUIRY";
		gotoxy(20,13);
		cout<<"5. ALL ACCOUNT HOLDER LIST";
		gotoxy(20,14);
		cout<<"6. CLOSE AN ACCOUNT";
		gotoxy(20,15);
		cout<<"7. MODIFY AN ACCOUNT";
		gotoxy(20,16);
		cout<<"8. EXIT";
		gotoxy(20,17);
		cout<<"Select Your Option (1-8): ";
		cin>>ch;

		switch(ch)
		{
		case '1':
			system("CLS");
			screen();
			writeAc();
			break;
		case '2':
			system("CLS");
			screen();
			gotoxy(15,8);
			cout<<"Enter The account No. : "; cin>>num;
			withdraw(num, 1);
			break;
		case '3':
			system("CLS");
			screen();
			gotoxy(15,8);
			cout<<"Enter The account No. : "; cin>>num;
			withdraw(num, 2);
			break;
		case '4':
			system("CLS");
			screen();
			gotoxy(15,8);
			cout<<"Enter The account No. : "; cin>>num;
			dispAc(num);
			break;
		case '5':
			screen();
			dispall();
			break;
		case '6':
			system("CLS");
			screen();
			gotoxy(15,8);
			cout<<"Enter The account No. : "; cin>>num;
			deleteAc(num);
			break;
		 case '7':
		 	system("CLS");
		 	screen();
		 	gotoxy(15,8);
			cout<<"Enter The account No. : "; cin>>num;
			modifyAc(num);
			break;
		 case '8':
		 	system("CLS");
		 	screen();
			cout<<"\n\n\n\n\t\t\tTHANK TO USING ME!";
			exit(0);
			break;
		 default :cout<<"\a";
		}
		cin.ignore();
		cin.get();
    }while(ch!='8');
	return ;
}


void writeAc()
{
	account ac;
	ofstream outFile;
	outFile.open("account.dat",ios::binary|ios::app);
	ac.createAc();
	outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
	outFile.close();
}

void dispAc(int n)
{
	account ac;
	bool flag=false;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		gotoxy(15,8);
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	system("CLS");
	screen();
	gotoxy(25,8);
	cout<<"BALANCE DETAILS";
    	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retAc()==n)
		{
			ac.showAc();
			flag=true;
		}
	}
    inFile.close();
    gotoxy(15,10);
	if(flag==false)
		cout<<"Account number does not exist";
}



void modifyAc(int n)
{
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		gotoxy(15,8);
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retAc()==n)
		{
			ac.showAc();
			gotoxy(22,18);
			cout<<"Enter The New Details of account"<<endl;
			gotoxy(22,19);
			cout<<"--------------------------------";
			ac.modify();
			int pos=(-1)*static_cast<int>(sizeof(account));
			File.seekp(pos,ios::cur); //fncallat1353
		    File.write(reinterpret_cast<char *> (&ac), sizeof(account));
		    gotoxy(15,24);
		    cout<<"Record Updated";
		    found=true;
		  }
	}
	File.close();
	gotoxy(15,10);
	if(found==false)
	cout<<"Record Not Found ";
}



void deleteAc(int n)
{
	account ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		gotoxy(15,8);
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Temp.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if(ac.retAc()!=n)
		{
			outFile.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
    inFile.close();
	outFile.close();
	remove("account.dat");
	rename("Temp.dat","account.dat");
	gotoxy(15,10);
	cout<<"Record Deleted ..";
}


void dispall()
{
	system("CLS");
	screen();
	account ac;
	int i=13;
	ifstream inFile;
	inFile.open("account.dat",ios::binary);
	if(!inFile)
	{
		gotoxy(15,8);
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	gotoxy(30,7);
	cout<<"ACCOUNT HOLDER LIST";
	gotoxy(30,8);
	cout<<"====================";
	gotoxy(15,10);
	cout<<"===================================================";
	gotoxy(15,11);
	cout<<"A/c no.      NAME           Type  	Balance\n";
	gotoxy(15,12);
	cout<<"===================================================\n";
	
	while(inFile.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		gotoxy(15,i);
		ac.report();
		i++;
	}
	inFile.close();
}


void withdraw(int n, int option)
{
	int amt;
	bool found=false;
	account ac;
	fstream File;
    File.open("account.dat", ios::binary|ios::in|ios::out);
	if(!File)
	{
		gotoxy(15,8);
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if(ac.retAc()==n)
		{
			ac.showAc();
			if(option==1)
			{
				gotoxy(25,18);
				cout<<"DEPOSITSS AMOUNT";
				gotoxy(25,19);
				cout<<"----------------";
				gotoxy(15,20);
				cout<<"Enter The amount to be deposited: ";
				cin>>amt;
				ac.dep(amt);
			}
		    if(option==2)
			{
				gotoxy(25,18);
				cout<<"WITHDRAW AMOUNT";
				gotoxy(25,19);
				cout<<"----------------";
				gotoxy(15,20);
				cout<<"Enter The amount to be withdraw: ";
				cin>>amt;
				int bal=ac.retdeposit()-amt;
				if(bal<0)
					cout<<"Insufficience balance";
				else
					ac.widr(amt);
		      }
			int pos=(-1)*static_cast<int>(sizeof(ac));
			File.seekp(pos,ios::cur);//fn1353
			File.write(reinterpret_cast<char *> (&ac), sizeof(account));
			gotoxy(15,22);
			cout<<"Record Updated";
			found=true;
	       }
         }
    File.close();
    gotoxy(15,10);
	if(found==false)
		cout<<"Record Not Found ";
}
void gotoxy(short x, short y)
{
	COORD pos ={x,y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void screen()
{
	int i;
	for(i=3;i<=75;i+=2)
	{
		gotoxy(i,1);
		cout<<"*";
		gotoxy(i,25);
		cout<<"*";
		gotoxy(i,6);
		cout<<"=";
	}
	for(i=1;i<=25;i++)
	{
		gotoxy(3,i);
		cout<<"*";
		gotoxy(75,i);
		cout<<"*";
	}
	gotoxy(27,3);
	cout<<"BANKING MANAGEMENT SYSTEM";
	gotoxy(31,4);
	cout<<"Bihar Bank Chapra";
}

void password()           /*function of password*/
{
	screen();
	char pass[10];
	char pass1[10]="samir123";
	char user[10];
	char user1[10]="Samir";
	int i=0 ;
	gotoxy(26,7);
	cout<<"LOGIN SCREEN";
	gotoxy(26,8);
	cout<<"------------";
	gotoxy(23,9);
	cout<<"User Name: ";
	gotoxy(23,11);
	cout<<"password: ";
	gotoxy(33,9);
	cin>>user;
	gotoxy(32,11);
	do
	{
		pass[i]=getch();
		if(pass[i]!='\r')
		{
			cout<<"*";
		}
		i++;
	}while(pass[i-1]!='\r');
		pass[i-1]='\0';
		if(strcmp(pass1,pass)==0&&strcmp(user1,user)==0)
		{
			system("cls");
			Main_Menu();
			getch();
		}
		else
		{
			gotoxy(23,13);
			printf("Invalied User or Password....");
		}

}
int main()
{
	
	system("cls");
	int n;
	while(1)
	{
		system("cls");
		screen();
		gotoxy(18,12);
		cout<<"W><E><L><C><O><M><E  T^O  P><R><O><J><E><C><T";
		gotoxy(23,14);
		cout<<">>-Project By: SAMIR KUMAR DUBEY-<<";
		gotoxy(30,24);
		cout<<"@Copyright Reserved";
		gotoxy(28,15);
		cout<<"Hit Any Key To Continue...";
		getch();
		system("cls");
		screen();
		gotoxy(12,14);
		cout<<"Enter <Samir> for User Name and <samir123> for Password.";
		gotoxy(26,15);
		cout<<"Hit Again Any Key To Continue...";
		getch();
		system("cls");
		screen();
		gotoxy(26,11);
		cout<<"1. Login";
		gotoxy(26,13);
		cout<<"2. Exit";
		gotoxy(26,15);
		cout<<"Enter Choice :";
		cin>>n;
		switch(n)
		{
			case 1:
				system("cls");
				password();
				break;
			case 2:
				exit(0);
				break;
			default :
				gotoxy(26,15);
				cout<<"INVALIED CHOICE...TRY AGAIN";
				getch();
				system("cls");
		}
	}
}
