subst_val (double x, const double *x0, int n0,
			 const double *x1, int n1)
{
    int i;

    for (i=0; i<n0; i++) {
	if (x == x0[i]) {
	    return (n1 == 1)? *x1 : x1[i];
	}
    }

    return x;
}
