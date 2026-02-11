mcumsum (header *hd)
{	header *result,*st=hd;
	double *m,*mr,sum=0,sumr=0,sumi=0;
	int r,c,i,j;
	hd=getvalue(hd); if (error) return;
	if (hd->type==s_real || hd->type==s_matrix)
	{	getmatrix(hd,&r,&c,&m);
		if (c<1) result=new_matrix(r,1,"");
		else result=new_matrix(r,c,"");
		if (error) return;
		mr=matrixof(result);
		for (i=0; i<r; i++)
		{	if (c>=1) sum=*m++;
			*mr++=sum;
			for (j=1; j<c; j++)
			{	sum+=*m++;
				*mr++=sum;
			}
		}
	}
	else if (hd->type==s_complex || hd->type==s_cmatrix)
	{	getmatrix(hd,&r,&c,&m);
		if (c<1) result=new_cmatrix(r,1,"");
		else result=new_cmatrix(r,c,"");
		if (error) return;
		mr=matrixof(result);
		for (i=0; i<r; i++)
		{	if (c>=1) { sumr=*m++; sumi=*m++; }
			*mr++=sumr; *mr++=sumi;
			for (j=1; j<c; j++)
			{	sumr+=*m++; *mr++=sumr;
				sumi+=*m++; *mr++=sumi;
			}
		}
	}
	else wrong_arg_in("cumsum");
	moveresult(st,result);
}
