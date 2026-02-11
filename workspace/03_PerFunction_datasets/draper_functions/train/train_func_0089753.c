minmax (double *x, long n, double *min, double *max,
	int *imin, int *imax)


{	long i;
	if (n==0)
	{	*min=0; *max=0; *imin=0; *imax=0; return; }
	*min=*x; *max=*x; *imin=0; *imax=0; x++;
	for (i=1; i<n; i++)
	{	if (*x<*min) { *min=*x; *imin=(int)i; }
		else if (*x>*max) { *max=*x; *imax=(int)i; }
		x++;
	}
}
