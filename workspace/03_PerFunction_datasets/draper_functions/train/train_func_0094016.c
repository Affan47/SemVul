quantile_interp (const double *y, int n,
			       double ftarg)
{
    double f, ret = NADBL;
    int i;

    for (i=0; i<n; i++) {
	f = plotpos(i+1, n);
	if (f >= ftarg) {
	    if (f > ftarg && i > 0) {
		double f0 = plotpos(i, n);
		double d = (ftarg - f0) / (f - f0);

		ret = (1-d) * y[i-1] + d * y[i];
	    } else {
		ret = y[i];
	    }
	    break;
	}
    }

    return ret;
}
