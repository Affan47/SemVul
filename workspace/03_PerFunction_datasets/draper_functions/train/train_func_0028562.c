rnchisq(double df, double lambda, RNG *rng)
{
    if (!R_FINITE(df) || !R_FINITE(lambda) || df < 0. || lambda < 0.)
	ML_ERR_return_NAN;

    if(lambda == 0.) {
	if (df == 0.) ML_ERR_return_NAN;
	return rgamma(df / 2., 2., rng);
    }
    else {
	double r = rpois( lambda / 2., rng);
	if (r > 0.)  r = rchisq(2. * r, rng);
	if (df > 0.) r += rgamma(df / 2., 2., rng);
	return r;
    }
}
