hermite_scale (int n, double *x, double *w,
			   double mu, double sigma)
{
    double rtpi = sqrt(M_PI);
    int i;

    for (i=0; i<n; i++) {
	x[i] = mu + M_SQRT2 * sigma * x[i];
	w[i] /= rtpi;
    }
}
