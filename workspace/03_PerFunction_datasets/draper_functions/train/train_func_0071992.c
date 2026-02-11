mshuffle (header *hd)
{  header *st=hd,*result;
	double *m,*mr,x;
	int i,j,n;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_matrix || dimsof(hd)->r!=1)
		wrong_arg_in("shuffle");
	n=dimsof(hd)->c;
	result=new_matrix(1,n,"");
	m=matrixof(hd); mr=matrixof(result);
	for (i=0; i<n; i++) *mr++=*m++;
	mr=matrixof(result);
	for (i=n-1; i>0; i--)
	{	j=(int)floor(ran2()*(i+1));
		if (i!=j)
		{	x=*(mr+i); *(mr+i)=*(mr+j); *(mr+j)=x;
		}
	}
	moveresult(st,result);

}
