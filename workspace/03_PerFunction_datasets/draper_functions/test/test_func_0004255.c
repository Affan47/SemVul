ccharpoly (double *m1, int n, double *p)


{	int *r,i,j,k;
	complex **m,h1,h2,g1,g2,*pc=(complex *)p;
	ctridiag(m1,n,&r); m=cmg;

	m[0][r[0]][0]=-m[0][r[0]][0];
	m[0][r[0]][1]=-m[0][r[0]][1];
	for (j=1; j<n; j++)
	{	m[0][r[j]][0]=-m[0][r[j]][0];
		m[0][r[j]][1]=-m[0][r[j]][1];
		for (k=1; k<=j; k++)
		{	h1[0]=-m[k][r[j]][0]; h1[1]=-m[k][r[j]][1];
			c_copy(h2,m[k][r[k-1]]);
			for (i=0; i<k; i++)
			{	c_mult(h2,m[i][r[j]],g1);
				c_mult(h1,m[i][r[k-1]],g2);
				c_add(g1,g2,m[i][r[j]]);
			}
			c_copy(m[k][r[j]],h1);
		}
		for (i=0; i<j; i++)
		{	c_add(m[i+1][r[j]],m[i][r[j-1]],m[i+1][r[j]]);
		}
	}
	for (i=0; i<n; i++) c_copy(pc[i],m[i][r[n-1]]);
	pc[n][0]=1.0; pc[n][1]=0.0;
}
