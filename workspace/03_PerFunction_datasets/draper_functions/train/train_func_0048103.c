mzeros (header *hd)
{	header *st=hd,*result;
	int r,c;
	double *m;
	hd=getvalue(hd); if (error) return;
	if (hd->type==s_matrix)
	{	make_complex(st); if (error) return;
		hd=getvalue(st); if (error) return;
	}
	if (hd->type!=s_cmatrix || dimsof(hd)->r!=1 || dimsof(hd)->c<2)
	{	output("Need a complex polynomial\n"); error=300; return; }
	getmatrix(hd,&r,&c,&m);
	result=new_cmatrix(1,c-1,""); if (error) return;
	bauhuber(m,c-1,matrixof(result),1,0,0);
	moveresult(st,result);
}
