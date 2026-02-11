mlusolve (header *hd)
{	header *st=hd,*hd1,*result;
	double *m,*m1;
	int r,c,r1,c1;
	hd=getvalue(hd);
	hd1=next_param(st);
	if (hd1) hd1=getvalue(hd1);
	if (error) return;
	if (hd->type==s_matrix || hd->type==s_real)
	{	getmatrix(hd,&r,&c,&m);
		if (hd1->type==s_cmatrix)
		{	make_complex(st);
			mlusolve(st); return;
		}
		if (hd1->type!=s_matrix && hd1->type!=s_real)
			wrong_arg_in("lu");
		getmatrix(hd1,&r1,&c1,&m1);
		if (c!=r || c<1 || r!=r1) wrong_arg_in("lu");
		result=new_matrix(r,c1,""); if (error) return;
		lu_solve(m,r,m1,c1,matrixof(result));
		if (error) return;
		moveresult(st,result);
	}
	else if (hd->type==s_cmatrix || hd->type==s_complex)
	{	getmatrix(hd,&r,&c,&m);
		if (hd1->type==s_matrix || hd1->type==s_real)
		{	make_complex(next_param(st));
			mlusolve(st); return;
		}
		if (hd1->type!=s_cmatrix && hd1->type!=s_complex)
			wrong_arg_in("lu");
		getmatrix(hd1,&r1,&c1,&m1);
		if (c!=r || c<1 || r!=r1) wrong_arg_in("lu");
		result=new_cmatrix(r,c1,""); if (error) return;
		clu_solve(m,r,m1,c1,matrixof(result));
		if (error) return;
		moveresult(st,result);
	}
	else wrong_arg_in("lu");
}
