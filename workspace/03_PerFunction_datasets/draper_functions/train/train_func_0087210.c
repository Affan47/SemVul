mfft (header *hd)
{	header *st=hd,*result;
	double *m,*mr;
	unsigned long nn[2];
	int r,c,i;
    long l;
	hd=getvalue(hd);
	if (error) return;
	if (hd->type==s_real || hd->type==s_matrix)
	{	make_complex(st); hd=st; }
	if (hd->type!=s_cmatrix && hd->type!=s_complex)
		wrong_arg_in("fft");
	getmatrix(hd,&r,&c,&m);
	result=new_cmatrix(r,c,""); if (error) return;
	mr=matrixof(result);
	memmove((char *)mr,(char *)m,(long)2*r*c*sizeof(double));
	if (r==1)
	{	fft(mr,c,1);
	}
	else
	{   nn[0]=r; nn[1]=c;
		for (l=1,i=0; i<20; i++,l*=2)
			if (l==r) goto cont1;
		goto err;
		cont1 :
		for (l=1,i=0; i<20; i++,l*=2)
			if (l==c) goto cont;
		err :
		output("fft columns must be a power of 2\n");
		error=1; return;
		cont :
		fftn(mr-1,nn,2,1);
	}
	if (error) return;
	moveresult(st,result);
}
