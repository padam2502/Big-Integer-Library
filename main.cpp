#include<iostream>
#include<string>
#include <algorithm>
using namespace std;

class Stack {
	int top;
public:
	string a[100005]; 
	Stack() { top = -1; }
	void push(string x);
	string pop();
	string peek();
	bool isEmpty();
};

void Stack::push(string x)
{
		a[++top]=x;
}

string Stack::pop()
{
		string x=a[top--];
		return x;
}
string Stack::peek()
{
		string x = a[top];
		return x;
}
bool Stack::isEmpty()
{
	return (top<0);
}

string remove0(string s)
{
    while(s[0]=='0' && s.size()>1)
    {
        s.erase(s.begin()+0);
    }
    return s;
}
string add(string s1,string s2)
{
    long long s=0;
    if(!s1.size())return s2;
    if(!s2.size())return s1;
    
	string t="";
	 reverse(s1.begin(), s1.end());
	  reverse(s2.begin(), s2.end());
	  int carry=0;
	  long long  m=min(s1.size(),s2.size());
	  for(long long i=0;i<m;i++)
	  {
	  	s=(s1[i]-'0')+(s2[i]-'0')+carry;
	  	carry=s/10;
	  	t.push_back((s%10)+'0');
	  }
	  if(s1.size()==m)
	  {
	  	for(long long i=m;i<s2.size();i++)
	  	{
	  		s=(s2[i]-'0')+carry;
	  		carry=s/10;
	  		t.push_back((s%10)+'0');
	  	}
	  }
	  else
	  {
	      for(long long i=m;i<s1.size();i++)
	  	{
	  		s=(s1[i]-'0')+carry;
	  		carry=s/10;
	  		t.push_back((s%10)+'0');
	  	}
	  }
	  if(carry)t.push_back(carry+'0');
	  reverse(t.begin(),t.end());
	  return t;
}
string subtract(string s1,string s2)
{
    if(s1.size()<s2.size()){return "-1";}
    	if(s1.size()==s2.size())
		{
			for(int i=0;i<s1.size();i++)
			{
				if(s1[i]-'0' < s2[i]-'0')
					{return "-1";}
				else if(s1[i]-'0' > s2[i]-'0')break;
			}
		}
    long long s=0;
	string t="";
	 reverse(s1.begin(), s1.end());
	  reverse(s2.begin(), s2.end());
	  int carry=0;
	  long long  m=min(s1.size(),s2.size());
	  for(long long i=0;i<m;i++)
	  {
	  	s=(s1[i]-'0')-(s2[i]-'0')-carry;
	  	if(s<0){s+=10;carry=1;}
	  	else
	  	{
	  		carry=0;
	  	}
	  	t.push_back((s)+'0');
	  }
	  	for(long long i=m;i<s1.size();i++)
	  	{
	  		s=(s1[i]-'0')-carry;
	  		if(s<0){s+=10;carry=1;}
	  	else
	  	{
	  		carry=0;
	  	}
	  	t.push_back((s)+'0');
	  	}
	  
	  reverse(t.begin(),t.end());
	  return (remove0(t));
	}
	string mul(string s1, string s2)
	{
		
		string res="";
		int z=-1;
	 reverse(s1.begin(), s1.end());
	  reverse(s2.begin(), s2.end());
	  for(int i=0;i<s2.size();i++)
	  {
	  	int carry=0;
	  	int s=0;
	  	string t="";
	  	++z;
	  	for(int j=0;j<s1.size();++j)
	  	{
	  		s=(s1[j]-'0')*(s2[i]-'0')+carry;
	  		t.push_back(s%10 + '0');
	  		carry=s/10;
	  	}
	  	if(carry)t.push_back(carry+'0');
	  	reverse(t.begin(),t.end());
	  	for(int l=0;l<z;l++){t.push_back('0');}
	  
	  	res=add(t,res);
	  }
	  return res;
	}
	string factorial(string s1)
	{
		long long n=0;
		for(int i=0;i<s1.size();i++)
		{
			n=n*10 +s1[i]-'0';
		}
		string res="1";
		for(int i=2;i<=n;i++)
		{
			string t= to_string(i);
			res=mul(res,t);
		}
		return res;
	}
	string exponentiation(string s1, long long n)
	{
		string res="1";
		if(!n){
			return res;
		}
		for(int i=1;i<=n;i++)
		{
			res=mul(res,s1);
		}
		return res;
	}
	string mod(string s1,string s2)
	{
		
		int n=s1.size();
		int m=s2.size();
		if(n < m)
		{
			return s1;
		}
		if(m==n)
		{
			for(int i=0;i<n;i++)
			{
				if(s1[i]-'0' < s2[i]-'0')
					{return s1;}
				else if(s1[i]-'0' > s2[i]-'0')break;
			}
		}
		
		string t= s1.substr(0,m+1);
		string rem=s1.substr(m,n);
		string res=t;
		string prev=res;
		do{
		    prev=res;
	    	res=subtract(res,s2);
	    }while(res!="-1");
		s1.replace(0,m+1,prev);
		return (mod(s1,s2));
	}
	string gcd(string s1,string s2)
	{
		if(s1.size()==1 && s1[0]=='0')return s2;
		return(gcd(mod(s2,s1),s1));
	}
	bool digit(char x)
	{
		if(x >= '0'  && x<='9')return true;
		return false;
	}
	int precedence(char x)
	{
		if(x=='+' || x=='-')return 1;
		else
			return 2;
	}
	string apply(string s1, string s2, string s3)
	{
		if(s3=="+")
		{
			return add(s1,s2);
		}
		else if(s3=="-")
		{
			return subtract(s1,s2);
		}
		else if(s3=="x")
		{
			return mul(s1,s2);
		}
	}
	string calc(string s)
	{
		string a,b;
		Stack val;
		Stack op;
		for(int i=0;i<s.size();i++)
		{
			if(digit(s[i]))
			{
				string f="";
				 while(i < s.size() && digit(s[i]))
				 {
				 	f.push_back(s[i]);
				 	++i;
				 }
				 i--;
				 val.push(f);
			}
			else
			{
			while(!op.isEmpty() && precedence(op.peek()[0]) >= precedence(s[i])){
                                
                string val2 = val.peek();
                val.pop();
                 
                string val1 = val.peek();
                val.pop();
                 
                string ch = op.peek();
                op.pop();
                 
                val.push(apply(val1, val2, ch));
           		 }
           		 string q="";
           		 q.push_back(s[i]);
           		 op.push(q);
        	}
		}
		while(!op.isEmpty()){
        string val2 = val.peek();
        val.pop();  
        string val1 = val.peek();
        val.pop();      
        string q = op.peek();
        op.pop();
               
        val.push(apply(val1, val2,q));
    	}	
    return val.peek();
}
int main()
{
	string s,t;
	char ch;
	//char choice ='y';
//	while(choice=='y' || choice=='Y'){
	//cout<<"Enter operation to be performed \n";
	//cout<<" 1 for exponentiation \n 2 for GCD of two numbers\n 3 for factorial \n 4 for Calculator \n ";
	cin>>ch;
	if(ch=='1')
	{
		long long p;
		cin>>s;
		cin>>p;
		cout<<exponentiation(s,p);
		//	cout<<"\nEnter Base\n";
		
	 //   cout<<"Enter Power\n";
	    
	    //cout<<" Answer is \n";
	    
		
	}
	else if(ch=='2')
	{
		//cout<<"Enter First Number\n";
		cin>>s;
		//cout<<"Enter Second Number\n";
		cin>>t;
		//cout<<" Answer is \n";
		cout<<gcd(s,t);
	
	}
	else if(ch=='3')
	{
		//cout<<"Enter the Number\n";
		cin>>s;
		//cout<<" Answer is \n";
	   cout<< factorial(s);
	}
	else if(ch=='4')
	{
		//cout<<"Enter String to be evaluated\n";
		cin>>s;
		//cout<<" Answer is \n";
		cout<<calc(s);
		
	}
	else
	{
		cout<<"Error\n";
	}
	//cout<<"\nWant to continue (y/n) \n";
	//cin>>choice;
	//}
	return 0;
}