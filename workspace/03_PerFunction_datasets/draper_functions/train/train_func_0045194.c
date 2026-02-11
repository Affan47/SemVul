mmatrix (header *hd)
{	header *st=hd,*hd1,*result;
	long i,n;
	double x,xi;
	double *m,*mr;
	int c,r,c1,r1;
	hd1=nextof(hd);
	hd=getvalue(hd);
	if (error) return;
	hd1=getvalue(hd1);
	if (error) return;
	if (hd->type==s_matrix)
	{	getmatrix(hd,&r,&c,&m);
		if (*m<0 || *m>INT_MAX || *(m+1)<0 || *(m+1)>INT_MAX)
			wrong_arg_in("matrix");
		r1=(int)*m; c1=(int)*(m+1);
		if (hd1->type==s_real)
		{	result=new_matrix(r1,c1,"");
			mr=matrixof(result);
			x=*realof(hd1);
			n=(long)c1*r1;
			for (i=0; i<n; i++) *mr++=x;
		}
		else if (hd1->type==s_complex)
		{	result=new_cmatrix(r1,c1,"");
			mr=matrixof(result);
			x=*realof(hd1); xi=*(realof(hd1)+1);
			n=(long)c1*r1;
			for (i=0; i<n; i++)
			{	*mr++=x; *mr++=xi;
			}
		}
		else wrong_arg_in("matrix");
	}
	else wrong_arg_in("matrix");
	moveresult(st,result);
}
