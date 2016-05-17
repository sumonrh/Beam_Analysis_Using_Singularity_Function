#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>
#include<math.h>
#include<stdio.h>
#include<string.h>
#include<dos.h>

void graphics_initilization();
void typewriter(char *text1);

class reaction{
	private:
	double R,pos;
	public:
	double R_shear(double x);
	double R_moment(double x);
	reaction(){R=0;pos=0;}
	~reaction(){}
	void set_reaction(double r){R=r;}
	void set_position(double y){pos=y;}
};

double reaction::R_shear(double x)
{
	double ans=0;
	double s1=0;
	if(x>pos)
	s1=1;
	ans=s1*R;
	return ans;
}
double reaction::R_moment(double x)
{
	double ans=0;
	double s1=0;
	if(x>pos)
	s1=1;
	ans=s1*R*(x-pos);
	return ans;
}

class pointload{
	private:
	double P,position;
	public:
	double p_shear(double x);
	double p_moment(double x);
	pointload(){P=0;position=0;}
	~pointload(){}
	void setload(double x,double y){P=x;position=y;}
	double getload()const{return P;}
	double getpos()const{return position;}
};


double pointload::p_shear(double x)
{
	double ans=0;
	double s1=0;
	if(x>position)
	s1=1;
	ans=-s1*P;
	return ans;
}
double pointload::p_moment(double x)
{
	double ans=0;
	double s1=0;
	if(x>position)
	s1=1;
	ans=-s1*P*(x-position);
	return ans;
}

class common{
	public:
	double max,st_pt,end_pt;
	void setload(double m,double s,double e){max=m;st_pt=s;end_pt=e;}
	double getload()const{return max;}
	double st_pos()const{return st_pt;}
	double end_pos()const{return end_pt;}

};

class uniformly_distributed_load:public common{
	public:
	double udl_shear(double  x);
	double udl_moment(double  x);
	uniformly_distributed_load(){max=0;st_pt=0;end_pt=0;}
	~uniformly_distributed_load(){}
};


double uniformly_distributed_load::udl_shear(double  x)
{
	double ans=0;
	double s1=0,s2=0;
	if(x>st_pt)
	s1=1;
	if(x>end_pt)
	s2=1;
	ans=-s1*max*(x-st_pt)+s2*max*(x-end_pt);
	return ans;
}

double uniformly_distributed_load::udl_moment(double  x)
{
	double ans=0;
	double s1=0,s2=0;
	if(x>st_pt)
	s1=1;
	if(x>end_pt)
	s2=1;
	ans=-s1*max*(x-st_pt)*(x-st_pt)/2+s2*max*(x-end_pt)*(x-end_pt)/2;
	return ans;

}

class uniformly_varying_load_increasing:public common{
	public:
	double uvl_shear(double  x);
	double uvl_moment(double  x);
	uniformly_varying_load_increasing(){max=0;st_pt=0;end_pt=0;}
	~uniformly_varying_load_increasing(){}

};

double uniformly_varying_load_increasing::uvl_shear(double  x)
{
	double ans=0;
	double s1=0,s2=0;
	if(x>st_pt)
	s1=1;
	if(x>end_pt)
	s2=1;
	ans=-s1*max*(x-st_pt)*(x-st_pt)/2/(end_pt-st_pt)+s2*max*(x-end_pt)+s2*max*(x-end_pt)*(x-end_pt)/(end_pt-st_pt)/2;
	return ans;
}

double uniformly_varying_load_increasing::uvl_moment(double  x)
{
	double ans=0;
	double s1=0,s2=0;
	if(x>st_pt)
	s1=1;
	if(x>end_pt)
	s2=1;
	ans=-s1*max*pow((x-st_pt),3)/6/(end_pt-st_pt)+s2*max*pow((x-end_pt),2)/2+s2*max*pow((x-end_pt),3)/(end_pt-st_pt)/6;
	return ans;
}


class uniformly_varying_load_decreasing:public common{
	public:
	double nuvl_shear(double  x);
	double nuvl_moment(double  x);
	uniformly_varying_load_decreasing(){max=0;st_pt=0;end_pt=0;}
	~uniformly_varying_load_decreasing(){}

};

double uniformly_varying_load_decreasing::nuvl_shear(double  x)
{
	double ans=0;
	double s1=0,s2=0;
	if(x>st_pt)
	s1=1;
	if(x>end_pt)
	s2=1;
	ans=-s1*max*(x-st_pt)+s1*max*pow((x-st_pt),2)/(end_pt-st_pt)/2-s2*max*pow((x-end_pt),2)/(end_pt-st_pt)/2;
	return ans;
}

double uniformly_varying_load_decreasing::nuvl_moment(double  x)
{
	double ans=0;
	double s1=0,s2=0;
	if(x>st_pt)
	s1=1;
	if(x>end_pt)
	s2=1;
	ans=-s1*max*pow((x-st_pt),2)/2+s1*max*pow((x-st_pt),3)/(end_pt-st_pt)/6-s2*max*pow((x-end_pt),3)/(end_pt-st_pt)/6;
	return ans;
}


class parabolic_load_increasing:public common{
	public:
	double parabolic_shear(double  x);
	double parabolic_moment(double  x);
	parabolic_load_increasing(){max=0;st_pt=0;end_pt=0;}
	~parabolic_load_increasing(){}

};

double parabolic_load_increasing::parabolic_shear(double  x)
{
	double ans=0;
	double s1=0,s2=0,l;
	l=end_pt-st_pt;
	if(x>st_pt)
	//ans=-max*pow((x-st_pt),3)/3/pow((end_pt-st_pt),2);
	s1=1;
	if(x>end_pt)
	s2=1;
	//ans=-max*(end_pt-st_pt)/3;
	ans=-s1*max*pow((x-st_pt),3)/(l*l)/3+s2*max*(x-end_pt)+s2*max*pow((x-end_pt),2)/l+s2*max*pow((x-end_pt),3)/(l*l)/3;
	return ans;
}

double parabolic_load_increasing::parabolic_moment(double  x)
{
	double ans=0;
	double s1=0,s2=0,l;
	l=end_pt-st_pt;
	if(x>st_pt)
	s1=1;
	//ans=-max*pow((x-st_pt),4)/pow((end_pt-st_pt),2)/12;
	if(x>end_pt)
	s2=1;
	//ans=-(max*(end_pt-st_pt)/3)*((x-end_pt)+(end_pt-st_pt)/4);
	ans=-s1*max*pow((x-st_pt),4)/(l*l)/12+s2*max*pow((x-end_pt),2)/2+s2*max*pow((x-end_pt),3)/3/l+s2*max*pow((x-end_pt),4)/(l*l)/12;
	return ans;
}

class parabolic_load_decreasing:public common{
	public:
	double dparabolic_shear(double  x);
	double dparabolic_moment(double  x);
	parabolic_load_decreasing(){max=0;st_pt=0;end_pt=0;}
	~parabolic_load_decreasing(){}

};

double parabolic_load_decreasing::dparabolic_shear(double  x)
{
	double ans=0;
	double s1=0,s2=0,l;
	l=end_pt-st_pt;
	if(x>st_pt)
	s1=1;
	if(x>end_pt)
	s2=1;
	ans=-s1*max*pow((x-st_pt),3)/(l*l)/3+s1*max*pow((x-st_pt),2)/l-s1*max*(x-st_pt)+s2*max*pow((x-end_pt),3)/(l*l)/3;
	return ans;
}

double parabolic_load_decreasing::dparabolic_moment(double  x)
{
	double ans=0;
	double s1=0,s2=0,l;
	l=end_pt-st_pt;
	if(x>st_pt)
	s1=1;
	if(x>end_pt)
	s2=1;
	ans=-s1*max*pow((x-st_pt),4)/(l*l)/12+s1*max*pow((x-st_pt),3)/l/3-s1*max*pow((x-st_pt),2)/2+s2*max*pow((x-end_pt),4)/(l*l)/12;
	return ans;
}

class concentrated_moment{
	private:
	double C,place;
	public:
	concentrated_moment(){C=0;place=0;}
	~concentrated_moment(){}
	double cm_moment(double x);
	void set_moment(double X,double Y){C=X;place=Y;}
	double get_moment()const{return C;}
	double get_pos()const{return place;}

};



double concentrated_moment::cm_moment(double x)
{
	double s1=0,ans=0;
	if(x>place)
	s1=1;
	ans=s1*C;
	return ans;

}



void main()
{
	clrscr();

	double m=0.5,P=0,Po=0,Wo=0,IWo=0,a=5,b=10,c=15,d=20,e=30,f=40,g=50,l=60,R1=0,R2=0,V,M,*shear,*moment,*length;
	double largest_shear=-9999999999.0,smallest_shear=9999999999.0,largest_moment=-9999999999.0,smallest_moment=9999999999.0;
	double r2=0,r1=0;
	int n;
	reaction OR1,OR2;
	pointload *PL;
	uniformly_distributed_load *UDL;
	uniformly_varying_load_increasing *UVL;
	uniformly_varying_load_decreasing *NUVL;
	parabolic_load_increasing *IPBL;
	parabolic_load_decreasing *DPBL;
	concentrated_moment *CM;


	textcolor(WHITE);
	textbackground(BLUE);
	clrscr();

	typewriter("\n    WELCOME TO THE SHEAR FORCE AND BENDING MOMENT DIAGRAM CREATING PROGRAM.");
	cout<<"\n\nENTER THE BEAM LENGTH :";
	cin>>l;

	cout<<"\nENTER THE POSITION OF LEFT SUPPORT :";
	cin>>r1;
	if(r1<0)
	{
		cout<<"\nINVALID DATA.";
		getch();
		exit(0);
	}
	cout<<"\nENTER THE POSITION OF RIGHT SUPPORT :";
	cin>>r2;
	if(r2<0||r2<r1)
	{
		cout<<"\nINVALID DATA.";
		getch();
		exit(0);
	}
	OR1.set_position(r1);
	OR2.set_position(r2);

	if(l<=0)
	{
		cout<<"\nINVALID BEAM LENGTH.";
		getch();
		exit(0);
	}

	cout<<"\nENTER THE NUMBER OF POINT LOADS :";
	cin>>n;
	PL=new pointload [n];

	for(int i=0;i<n;i++)
	{
		cout<<"\nENTER THE MAGNITUDE OF THE POINT LOAD P["<<(i+1)<<"] :";
		cin>>P;
		if(P!=0)
		{
			cout<<"\nENTER ITS POSITION FROM LEFT : ";
			cin>>a;
			if(a<0||a>l)
			{
				cout<<"\nTHE VALUE OF A MUST BE GREATER THAN ZERO OR SMALLER THAN BEAM LENGTH.";
				getch();
				exit(0);
			}
		}
		PL[i].setload(P,a);
	}
	int nud=0;
	cout<<"\nENTER THE NUMBER OF UDL : ";
	cin>>nud;
	UDL=new uniformly_distributed_load[nud];
	for(i=0;i<nud;i++)
	{
		cout<<"\nENTER THE VALUE OF UDL Po["<<(i+1)<<"] :";
		cin>>Po;
		if(Po!=0)
		{
			cout<<"\nENTER THE STARTING POINT FROM LEFT :";
			cin>>b;
			cout<<"\nENTER THE ENDING POINT FROM LEFT :";
			cin>>c;
			if(b<0||b>=c)
			{
				cout<<"\nTHE STARTING POINT MUST BE GREATER THAN ZERO OR SMALLER THAN ENDING POINT.";
				getch();
				exit(0);
			}
			if(c<b||c>l)
			{
				cout<<"\nTHE ENDING POINT MUST BE GREATER THAN STARTING POINT\
				OR SMALLER THAN BEAM LENGTH.";
				getch();
				exit(0);
			}
		}
		UDL[i].setload(Po,b,c);
	}

	int nuvli=0;
	cout<<"\nENTER THE NUMBER OF UVL [INCREASING LOAD] :";
	cin>>nuvli;
	UVL=new uniformly_varying_load_increasing [nuvli];
	for(i=0;i<nuvli;i++)
	{
		cout<<"\nENTER THE MAX VALUE OF UVL [INCREASING LOAD] Wo["<<(i+1)<<"]: ";
		cin>>Wo;
		if(Wo!=0)
		{
			cout<<"\nENTER THE STARTING POINT FROM LEFT :";
			cin>>d;
			cout<<"\nENTER THE ENDING POINT FROM LEFT :";
			cin>>e;
			if(e<d||d>l)
			{
				cout<<"\nTHE ENDING POINT MUST BE GREATER THAN STARTING POINT \
				OR SMALLER THAN BEAM LENGTH.";
				getch();
				exit(0);
			}
		}
		UVL[i].setload(Wo,d,e);
	}
	int nuvld=0;
	cout<<"\nENTER THE NUMBER OF UVL [DECREASING LOAD] :";
	cin>>nuvld;

	NUVL=new uniformly_varying_load_decreasing [nuvld];
	for(i=0;i<nuvld;i++)
	{
		cout<<"\nENTER THE MAX VALUE OF UVL [DECREASING LOAD] Wo["<<(i+1)<<"] :";
		cin>>IWo;
		if(IWo!=0)
		{
			cout<<"\nENTER THE STARTING POINT FROM LEFT :";
			cin>>f;
			cout<<"\nENTER THE ENDING POINT FROM LEFT :";
			cin>>g;
			if(g<f||f>l)
			{
				cout<<"\nTHE ENDING POINT MUST BE GREATER THAN STARTING POINT\OR SMALLER THAN BEAM LENGTH.";
				getch();
				exit(0);
			}
		}
		NUVL[i].setload(IWo,f,g);
	}

	int npbl;
	cout<<"\nENTER THE NUMBER OF PARABOLIC LOAD [INCREASING] :";
	cin>>npbl;
	IPBL=new parabolic_load_increasing [npbl];
	double Yo,h,I;
	for(i=0;i<npbl;i++)
	{
		cout<<"\nENTER THE MAX VALUE OF PARABOLIC LOAD Yo["<<i+1<<"] :";
		cin>>Yo;
		if(Yo!=0)
		{
			cout<<"\nENTER THE STARTING POINT FROM LEFT :";
			cin>>h;
			cout<<"\nENTER THE ENDING POINT FROM LEFT :";
			cin>>I;
			if(I<h||I>l)
			{
				cout<<"\nTHE ENDING POINT MUST BE GREATER THAN STARTING POINT\OR SMALLER THAN BEAM LENGTH.";
				getch();
				exit(0);
			}
		}
		IPBL[i].setload(Yo,h,I);
	}

	int ndpbl;
	cout<<"\nENTER THE NUMBER OF PARABOLIC LOAD [DECREASING] :";
	cin>>ndpbl;
	DPBL=new parabolic_load_decreasing [ndpbl];
	//double Yo,h,I;
	for(i=0;i<ndpbl;i++)
	{
		cout<<"\nENTER THE MAX VALUE OF PARABOLIC LOAD Yo["<<i+1<<"] :";
		cin>>Yo;
		if(Yo!=0)
		{
			cout<<"\nENTER THE STARTING POINT FROM LEFT :";
			cin>>h;
			cout<<"\nENTER THE ENDING POINT FROM LEFT :";
			cin>>I;
			if(I<h||I>l)
			{
				cout<<"\nTHE ENDING POINT MUST BE GREATER THAN STARTING POINT\OR SMALLER THAN BEAM LENGTH.";
				getch();
				exit(0);
			}
		}
		DPBL[i].setload(Yo,h,I);
	}

	int ncm;
	cout<<"\nENTER NUMBER OF CONCENTRATED MOMENT :";
	cin>>ncm;
	CM=new concentrated_moment[ncm];
	double Z,pcm;
	for(i=0;i<ncm;i++)
	{
		cout<<"\nENTER THE VALUE OF CONCENTRATED MOMENT ["<<(i+1)<<"] :";
		cin>>Z;
		if(Z!=0)
		{
			cout<<"\nENTER ITS POSITION FROM LEFT :";
			cin>>pcm;
			if(pcm<0||pcm>l)
			{
				cout<<"\nINVALID POSITION.";
				getch();
				exit(0);
			}

		}
		CM[i].set_moment(Z,pcm);
	}


	shear=new double[l*(1/m)+n+ncm+4];
	moment=new double[l*(1/m)+n+ncm+4];
	length=new double[l*(1/m)+n+ncm+4];

	if(shear==NULL||moment==NULL||length==NULL)
	{
		cout<<"\nAN ERROR HAS OCCURED WHILE ALLOCATING MEMOMY SPACE.";
		getch();
		exit(0);
	}
	for(i=0;i<(l*(1/m)+n+ncm+4);i++)
	{
		shear[i]=0.0;
		moment[i]=0.0;
		length[i]=0.0;
	}

	double reaction_comp_pl1=0,total_pl=0;
	for(int j=0;j<n;j++)
	{
		reaction_comp_pl1+=PL[j].getload()*(r2-PL[j].getpos());
		total_pl+=PL[j].getload();
	}

	double reaction_comp_udl1=0,total_udl=0;
	for(j=0;j<nud;j++)
	{
		reaction_comp_udl1+=.5*UDL[j].getload()*(r2-UDL[j].st_pos())*(r2-UDL[j].st_pos())-.5*UDL[j].getload()*(r2-UDL[j].end_pos())*(r2-UDL[j].end_pos());
		total_udl+=UDL[j].getload()*(l-UDL[j].st_pos())-UDL[j].getload()*(l-UDL[j].end_pos());
	}

	double uvls=0,uvlm=0,nuvls=0,nuvlm=0;

	for(i=0;i<nuvli;i++)
	{
		uvlm+=UVL[i].getload()*pow((r2-UVL[i].st_pos()),3)/(UVL[i].end_pos()-UVL[i].st_pos())/6-UVL[i].getload()*(r2-UVL[i].end_pos())*(r2-UVL[i].end_pos())/2-UVL[i].getload()*pow((r2-UVL[i].end_pos()),3)/(UVL[i].end_pos()-UVL[i].st_pos())/6;
		uvls+=UVL[i].getload()*(l-UVL[i].st_pos())*(l-UVL[i].st_pos())/2/(UVL[i].end_pos()-UVL[i].st_pos())-UVL[i].getload()*(l-UVL[i].end_pos())-UVL[i].getload()*(l-UVL[i].end_pos())*(l-UVL[i].end_pos())/2/(UVL[i].end_pos()-UVL[i].st_pos());
	}

	for(i=0;i<nuvld;i++)
	{
		nuvlm+=NUVL[i].getload()*pow((r2-NUVL[i].st_pos()),2)/2-NUVL[i].getload()*pow((r2-NUVL[i].st_pos()),3)/(NUVL[i].end_pos()-NUVL[i].st_pos())/6+NUVL[i].getload()*pow((r2-NUVL[i].end_pos()),3)/(NUVL[i].end_pos()-NUVL[i].st_pos())/6;
		nuvls+=-NUVL[i].getload()*(l-NUVL[i].st_pos())*(l-NUVL[i].st_pos())/2/(NUVL[i].end_pos()-NUVL[i].st_pos())+NUVL[i].getload()*(l-NUVL[i].st_pos())+NUVL[i].getload()*(l-NUVL[i].end_pos())*(l-NUVL[i].end_pos())/2/(NUVL[i].end_pos()-NUVL[i].st_pos());
	}
	double pbls=0,pblm=0;
	for(i=0;i<npbl;i++)
	{
		pblm+=(IPBL[i].getload()*(IPBL[i].end_pos()-IPBL[i].st_pos())*(((r2-IPBL[i].end_pos())+(IPBL[i].end_pos()-IPBL[i].st_pos())/4)))/3;
		pbls+=IPBL[i].getload()*(IPBL[i].end_pos()-IPBL[i].st_pos())/3;
	}

	double dpbls=0,dpblm=0;
	for(i=0;i<ndpbl;i++)
	{
		dpblm+=(DPBL[i].getload()*(DPBL[i].end_pos()-DPBL[i].st_pos())*(((r2-DPBL[i].end_pos())+3*(DPBL[i].end_pos()-DPBL[i].st_pos())/4)))/3;
		dpbls+=DPBL[i].getload()*(DPBL[i].end_pos()-DPBL[i].st_pos())/3;
	}

	double cmm=0;
	for(i=0;i<ncm;i++)
	{
		cmm+=-CM[i].get_moment();
	}

	R1=(reaction_comp_pl1+reaction_comp_udl1+uvlm+nuvlm+cmm+pblm+dpblm)/(r2-r1);
	R2=-R1+total_pl+total_udl+uvls+nuvls+pbls+dpbls;
	OR1.set_reaction(R1);
	OR2.set_reaction(R2);
	cout<<"\nLEFT SUPPORT REACTION : "<<R1;
	cout<<"\nRIGHT SUPPORT REACTION : "<<R2<<endl;
	getch();

	cout<<"FEET    SHEAR    MOMENT"<<endl;
	i=0;
	for(double x=0;x<=l;x+=m)
	{
		if(x==0)
		{
			length[i]=0.0;
			shear[i]=0.0;
			moment[i]=0.0;
			i++;
		}

		double total_plv=0,total_plm=0;
		for(j=0;j<n;j++)
		{
			total_plv+=PL[j].p_shear(x);
			total_plm+=PL[j].p_moment(x);
		}
		double total_udlv=0,total_udlm=0;
		for(j=0;j<nud;j++)
		{
			total_udlv+=UDL[j].udl_shear(x);
			total_udlm+=UDL[j].udl_moment(x);
		}

		double total_uvls=0,total_uvlm=0;
		for(j=0;j<nuvli;j++)
		{
			total_uvls+=UVL[j].uvl_shear(x);
			total_uvlm+=UVL[j].uvl_moment(x);
		}

		double total_nuvls=0,total_nuvlm=0;
		for(j=0;j<nuvld;j++)
		{
			total_nuvls+=NUVL[j].nuvl_shear(x);
			total_nuvlm+=NUVL[j].nuvl_moment(x);
		}

		double total_pbls=0,total_pblm=0;
		for(j=0;j<npbl;j++)
		{
			total_pbls+=IPBL[j].parabolic_shear(x);
			total_pblm+=IPBL[j].parabolic_moment(x);
		}

		double total_dpbls=0,total_dpblm=0;
		for(j=0;j<ndpbl;j++)
		{
			total_dpbls+=DPBL[j].dparabolic_shear(x);
			total_dpblm+=DPBL[j].dparabolic_moment(x);
		}

		double total_cmm=0;
		for(j=0;j<ncm;j++)
		{
			total_cmm+=CM[j].cm_moment(x);
		}
		double R1_shear=0,R1_moment=0,R2_shear=0,R2_moment=0;
		R1_shear=OR1.R_shear(x);
		R1_moment=OR1.R_moment(x);
		R2_shear=OR2.R_shear(x);
		R2_moment=OR2.R_moment(x);

		V=R1_shear+R2_shear+total_plv+total_udlv+total_uvls+total_nuvls+total_pbls+total_dpbls;
		M=R1_moment+R2_moment+total_plm+total_udlm+total_uvlm+total_nuvlm+total_cmm+total_pblm+total_dpblm;

		length[i]=x;
		shear[i]=V;
		moment[i]=M;
		i++;
		cout<<x<<"\t"<<V<<"\t"<<M<<endl;

		if(x==r1)
		{
			V=V+R1;
			length[i]=x;
			shear[i]=V;
			moment[i]=M;
			i++;
			cout<<x<<"\t"<<V<<"\t"<<M<<endl;
		}

		for(j=0;j<n;j++)
		{
			if(x==PL[j].getpos())
			{
				V=V-PL[j].getload();
				length[i]=x;
				shear[i]=V;
				moment[i]=M;
				cout<<x<<"\t"<<V<<"\t"<<M<<endl;
				i++;
			}
		}
		for(j=0;j<ncm;j++)
		{
			if(x==CM[j].get_pos())
			{
				M=M+CM[j].get_moment();
				length[i]=x;
				shear[i]=V;
				moment[i]=M;
				cout<<x<<"\t"<<V<<"\t"<<M<<endl;
				i++;
			}
		}
		if(x==r2)
		{
			V=V+R2;
			length[i]=x;
			shear[i]=V;
			moment[i]=M;
			i++;
			cout<<x<<"\t"<<V<<"\t"<<M<<endl;
		}

		if(i%23==0)
		{
			cout<<"PRESS ANY KEY TO CONTINUE."<<endl;
			getch();
		}
	}
	getch();

	double lim=(i-1);
	for(i=0;i<lim;i++)
	{
		if(largest_shear<shear[i])
		{
			largest_shear=shear[i];
		}
		if(smallest_shear>shear[i])
		{
			smallest_shear=shear[i];
		}
		if(largest_moment<moment[i])
		{
			largest_moment=moment[i];
		}
		if(smallest_moment>moment[i])
		{
			smallest_moment=moment[i];
		}

	}

	graphics_initilization();

	setbkcolor(LIGHTBLUE);
	setcolor(WHITE);
	gotoxy(34,2);
	cout<<"SHEAR FORCE DIAGRAM";
	outtextxy(450, 310, "BEAM LENGTH (ft)");
	outtextxy(10, 50, "Kip");

	line(50,300,600,300);  //X axis
	line(50,500,50,10);    //Y axis

	double shear_scale=150/(largest_shear+fabs(smallest_shear));

	char msg[80];


	for(double incr=.25;incr<=1;incr+=.25)
	{
		sprintf(msg, "%.1f", (double far)smallest_shear*incr);
		outtextxy(15,300-(int)(shear_scale*smallest_shear*incr), msg);
	}

	for(incr=.25;incr<=1;incr+=.25)
	{
		sprintf(msg, "%.1f", (double far)largest_shear*incr);
		outtextxy(15,300-(int)(shear_scale*largest_shear*incr) , msg);
	}

	for(incr=.25;incr<=1;incr+=.25)
	{
		sprintf(msg, "%.1f",(double far)l*incr);
		outtextxy((int)(50+(350.0/l)*l*incr), 305, msg);
	}


	j=0;
	moveto(50,300); //Origin
	for(x=0;x<=lim;x++)
	{
		lineto((int)(50+(350.0/l)*length[j]),(int)(300-shear_scale*shear[j]));
		//putpixel(50+(350.0/l)*length[j],300-shear_scale*shear[j],WHITE);
		j++;
	}
	//lineto(50+(350.0/l)*length[--j],300);
	getch();
	closegraph();

	graphics_initilization();
	setbkcolor(LIGHTBLUE);
	setcolor(WHITE);
	gotoxy(34,2);
	cout<<"BENDING MOMENT DIAGRAM";
	outtextxy(450, 310, "BEAM LENGTH (ft)");
	outtextxy(1, 50, "Kip-ft");
	line(50,300,600,300);//X axis
	line(50,500,50,10);  //Y axis

	double moment_scale=150/(largest_moment+fabs(smallest_moment));

	for(incr=.25;incr<=1;incr+=.25)
	{
		sprintf(msg, "%.1f", (double far)smallest_moment*incr);
		outtextxy(15,300-(int)(moment_scale*smallest_moment*incr),msg);
	}

	for(incr=.25;incr<=1;incr+=.25)
	{
		sprintf(msg, "%.1f", (double far)largest_moment*incr);
		outtextxy(15,300-(int)(moment_scale*largest_moment*incr) , msg);
	}
	for(incr=.25;incr<=1;incr+=.25)
	{
		sprintf(msg, "%.1f",(double far)l*incr);
		outtextxy((int)(50+(350.0/l)*l*incr), 305, msg);
	}

	j=0;
	moveto(50,300); //Origin
	for(x=0;x<=lim;x++)
	{
		lineto((int)(50+(350.0/l)*length[j]),(int)(300-moment_scale*moment[j]));
		//putpixel(50+(350.0/l)*length[j],300-moment_scale*moment[j],WHITE);
		j++;
	}
	getch();
	delete []shear;
	delete []moment;
	delete []length;
	closegraph();
}

void graphics_initilization()
{
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;

	/* initialize graphics and local variables */
	initgraph(&gdriver, &gmode, "d:\\tc\\bgi");

	/* read result of initialization */
	errorcode = graphresult();
	/* an error occurred */
	if (errorcode != grOk)
	{
		cout<<"Graphics error: \n"<<grapherrormsg(errorcode);
		cout<<"Press any key to halt:";
		getch();
		exit(1);    /* terminate with an error code */
	}

}

void typewriter(char *text1)
{
	int s_len;
	s_len=strlen(text1);
	for(int i=0;i<s_len;i++)
	{
	    cout<<text1[i];
	    sound(650);
	    delay(25);
	    nosound();

	}

}
