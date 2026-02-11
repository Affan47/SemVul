mpswindow (header *hd)
{	double *m;
	double c,r;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_matrix || dimsof(hd)->r!=1 || dimsof(hd)->c!=2)
	{	output("Arguments for pswindow are [c r]!\n");
		error=90; return;
	}
	m=matrixof(hd);
	c=*m++;
	r=*m;
	if (c<1) c=1;
	if (r<1) r=1;
    pswindow(c,r);
}
