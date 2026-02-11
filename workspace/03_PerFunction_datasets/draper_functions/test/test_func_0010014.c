cpeval (double *x, double *xi, double *z, double *zi)
{	int i;
	double *p,h,hi;
	p=polynom+(2l*degree);
	*z=*p; *zi=*(p+1);
	p-=2;
	for (i=degree-1; i>=0; i--)
	{	complex_multiply(x,xi,z,zi,&h,&hi);
		*z= h + *p;
		*zi=hi+*(p+1); p-=2;
	}
}
