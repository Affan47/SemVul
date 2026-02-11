matrix_CpABt_double (double* C,double* A,double* B,size_t n,size_t p,size_t m)
{
	double r;
	size_t i,j,k;
	for (k=0;k<p;k++)
	{
		for (j=0;j<m;j++)
		{
			r = B[j+k*m];
			for (i=0;i<n;i++)
				C[i+j*n] += r*A[i+k*n];
		}
	}
}
