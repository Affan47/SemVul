qsignrank(double x, double n, int lower_tail, int log_p)
{
    double f, p;

#ifdef IEEE_754
    if (ISNAN(x) || ISNAN(n))
	return(x + n);
#endif
    if (!R_FINITE(x) || !R_FINITE(n))
	ML_ERR_return_NAN;
    R_Q_P01_check(x);

    n = floor(n + 0.5);
    if (n <= 0)
	ML_ERR_return_NAN;

    if (x == R_DT_0)
	return(0);
    if (x == R_DT_1)
	return(n * (n + 1) / 2);

    if(log_p || !lower_tail)
	x = R_DT_qIv(x);

    int nn = (int) n;
    w_init_maybe(nn);
    f = exp(- n * M_LN2);
    p = 0;
    int q = 0;
    if (x <= 0.5) {
	x = x - 10 * DBL_EPSILON;
	for (;;) {
	    p += csignrank(q, nn) * f;
	    if (p >= x)
		break;
	    q++;
	}
    }
    else {
	x = 1 - x + 10 * DBL_EPSILON;
	for (;;) {
	    p += csignrank(q, nn) * f;
	    if (p > x) {
		q = (int)(n * (n + 1) / 2 - q);
		break;
	    }
	    q++;
	}
    }

    return(q);
}
