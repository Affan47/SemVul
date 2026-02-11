multistepjacobian(int n, real_t x, real_t y[], real_t eps,
			real_t fixy[], real_t fixdy[], real_t dy[], real_t **jacobian,
			void (*deriv)(real_t [], int, real_t, real_t[]),
			int (*available)(int, real_t, real_t [], real_t **),
			int *evaluate, int *decompose, int *evaluated)
{


	int i,j;
	real_t d;

	*evaluate = 0;
	*decompose = *evaluated = 1;
	if (!(*available)(n,x,y,jacobian)) {
		for (i=1; i<=n; i++) fixy[i]=y[i];
		(*deriv)(fixdy,n,x,y);
		for (j=1; j<=n; j++) {
			d=((eps > fabs(fixy[j])) ? eps*eps : eps*fabs(fixy[j]));
			y[j] += d;
			(*deriv)(dy,n,x,y);
			for (i=1; i<=n; i++) jacobian[i][j]=(dy[i]-fixdy[i])/d;
			y[j]=fixy[j];
		}
	}
}
