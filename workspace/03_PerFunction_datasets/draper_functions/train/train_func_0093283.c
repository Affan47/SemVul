runge1 (double a, double b, int steps, double y[], int n,
	char *fname, int argn, header *args, long size)
{	int i,k;
	double x,h;
	double *vout,*dv;
	vout=(double *)malloc(n*sizeof(double));
	dv=(double *)malloc(n*sizeof(double));
	dym=(double *)malloc(n*sizeof(double));
	dyt=(double *)malloc(n*sizeof(double));
	yt=(double *)malloc(n*sizeof(double));
	x=a;
	h=(b-a)/steps;
	for (k=0; k<steps; k++)
	{   if (test_key()==escape) { error=1; goto stop; }
		fevaldgl(x,y,dv,n,fname,argn,args,size);
		if (error) goto stop;
		rk4(y,dv,n,x,h,vout,fname,argn,args,size);
		if (error) goto stop;
		x += h;
		for (i=0; i<n; i++) y[i]=vout[i];
	}
	stop :
	free(vout);
	free(dv);
	free(dym);
	free(dyt);
	free(yt);
}
