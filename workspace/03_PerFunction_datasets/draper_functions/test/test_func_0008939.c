pexp(double x, double scale, int lower_tail, int log_p)
{
#ifdef IEEE_754
    if (ISNAN(x) || ISNAN(scale))
	return x + scale;
    if (scale < 0) ML_ERR_return_NAN;
#else
    if (scale <= 0) ML_ERR_return_NAN;
#endif

    if (x <= 0.)
	return R_DT_0;

    x = -(x / scale);
    if (lower_tail)
	return (log_p

		? (x > -M_LN2 ? log(-expm1(x)) : log1p(-exp(x)))
		: -expm1(x));

    return R_D_exp(x);
}
