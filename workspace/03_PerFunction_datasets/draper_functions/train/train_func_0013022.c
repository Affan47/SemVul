gretl_get_cdf (int dist, const double *parm, double x)
{
    double y = NADBL;

    if (pdist_check_input(dist, parm, x) == E_MISSDATA) {
	return y;
    }

    if (dist == D_NORMAL) {
	y = normal_cdf(x);
    } else if (dist == D_STUDENT) {
	y = student_cdf(parm[0], x);
    } else if (dist == D_CHISQ) {
	y = chisq_cdf((int) parm[0], x);
    } else if (dist == D_SNEDECOR) {
	y = snedecor_cdf((int) parm[0], (int) parm[1], x);
    } else if (dist == D_GAMMA) {
	y = gamma_cdf(parm[0], parm[1], x, 1);
    } else if (dist == D_BINOMIAL) {
	y = binomial_cdf(parm[0], (int) parm[1], (int) x);
    } else if (dist == D_POISSON) {
	y = poisson_cdf(parm[0], (int) x);
    } else if (dist == D_WEIBULL) {
	y = weibull_cdf(parm[0], parm[1], x);
    } else if (dist == D_GED) {
	y = GED_cdf(parm[0], x);
    }

    return y;
}
