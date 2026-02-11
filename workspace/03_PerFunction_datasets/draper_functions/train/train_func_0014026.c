gretl_acf (int k, int t1, int t2, const double *y,
			 double ybar)
{
    double z, num = 0, den = 0;
    int t, n = 0;

    for (t=t1; t<=t2; t++) {
	if (na(y[t])) {
	    return NADBL;
	}
	z = y[t] - ybar;
	den += z * z;
	if (t - k >= t1) {
	    if (na(y[t-k])) {
		return NADBL;
	    }
	    num += z * (y[t-k] - ybar);
	    n++;
	}
    }

    if (n == 0) {
	return NADBL;
    }

    return num / den;
}
