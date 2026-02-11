projgr_(int n, double *l, double *u,
		    int *nbd, double *x, double *g,
		    double *sbgnrm)
{
    double d1, d2, gi;
    int i;

    *sbgnrm = 0;

    for (i = 0; i < n; ++i) {
	gi = g[i];
	if (nbd[i] != 0) {
	    if (gi < 0) {
		if (nbd[i] >= 2) {
		    d1 = x[i] - u[i];
		    gi = max(d1, gi);
		}
	    } else {
		if (nbd[i] <= 2) {
		    d1 = x[i] - l[i];
		    gi = min(d1, gi);
		}
	    }
	}
	d1 = *sbgnrm, d2 = fabs(gi);
	*sbgnrm = max(d1, d2);
    }
}
