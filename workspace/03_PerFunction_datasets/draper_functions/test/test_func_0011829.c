punif(double x, double a, double b, int lower_tail, int log_p)
{
#ifdef IEEE_754
    if (ISNAN(x) || ISNAN(a) || ISNAN(b))
	return x + a + b;
#endif
    if (b < a) ML_ERR_return_NAN;
    if (!R_FINITE(a) || !R_FINITE(b)) ML_ERR_return_NAN;

    if (x >= b)
	return R_DT_1;
    if (x <= a)
	return R_DT_0;
    if (lower_tail) return R_D_val((x - a) / (b - a));
    else return R_D_val((b - x) / (b - a));
}
