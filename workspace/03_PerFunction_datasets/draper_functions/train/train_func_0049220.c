dbinom(double x, double n, double p, int give_log)
{
#ifdef IEEE_754

    if (ISNAN(x) || ISNAN(n) || ISNAN(p)) return x + n + p;
#endif

    if (p < 0 || p > 1 || R_D_negInonint(n))
	ML_ERR_return_NAN;
    R_D_nonint_check(x);
    if (x < 0 || !R_FINITE(x)) return R_D__0;

    n = R_D_forceint(n);
    x = R_D_forceint(x);

    return dbinom_raw(x, n, p, 1-p, give_log);
}
