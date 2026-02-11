lchoose(double n, double k)
{
    double k0 = k;
    k = floor(k + 0.5);
#ifdef IEEE_754

    if(ISNAN(n) || ISNAN(k)) return n + k;
#endif
    if (fabs(k - k0) > 1e-7)
	MATHLIB_WARNING2(_("'k' (%.2f) must be integer, rounded to %.0f"), k0, k);
    if (k < 2) {
	if (k <	 0) return ML_NEGINF;
	if (k == 0) return 0.;

	return log(n);
    }

    if (n < 0) {
	if (ODD(k)) return ML_NAN;
	return lchoose(-n+ k-1, k);
    }
    else if (R_IS_INT(n)) {
	n = floor(n + 0.5);
	if(n < k) return ML_NEGINF;
	if(n - k < 2) return lchoose(n, n-k);
	return lfastchoose(n, k);
    }

    if (n < k-1) {
	int s;
	if (fmod(floor(n-k+1), 2.) == 0)
	    return ML_NAN;
	return lfastchoose2(n, k, &s);
    }
    return lfastchoose(n, k);
}
