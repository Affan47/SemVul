mdiag2 (header *hd)
{	header *st=hd,*hd1,*result;
	int c,r,i,n,l;
	double *m,*mh,*mr;
	hd1=next_param(hd);
	hd=getvalue(hd); if (hd1) hd1=getvalue(hd1);
	if (error) return;
	if (hd1->type!=s_real) wrong_arg();
	n=(int)*realof(hd1);
	if (hd->type==s_matrix || hd->type==s_real)
	{	getmatrix(hd,&r,&c,&m);
		result=new_matrix(1,r,""); if (error) return;
		mr=matrixof(result); l=0;
		for (i=0; i<r; i++)
		{	if (i+n>=c) break;
			if (i+n>=0) { l++; *mr++=*mat(m,c,i,i+n); }
		}
		dimsof(result)->c=l;
		result->size=matrixsize(1,c);
	}
	else if (hd->type==s_cmatrix || hd->type==s_complex)
	{	getmatrix(hd,&r,&c,&m);
		result=new_cmatrix(1,r,""); if (error) return;
		mr=matrixof(result); l=0;
		for (i=0; i<r; i++)
		{	if (i+n>=c) break;
			if (i+n>=0)
			{	l++;
				mh=cmat(m,c,i,i+n);
				*mr++=*mh++;
				*mr++=*mh;
			}
		}
		dimsof(result)->c=l;
		result->size=cmatrixsize(1,c);
	}
	else wrong_arg();
	moveresult(st,result);
}
