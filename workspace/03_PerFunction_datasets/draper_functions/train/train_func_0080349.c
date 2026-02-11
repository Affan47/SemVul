GED_cdf_inverse (double nu, double a)
{
    if (nu > 0 && a < 1 && a > 0) {
	double a2, p, lg1, lg3, sd, x;
	int sgn;

	if (a > 0.5) {
	    a2 = 2*a - 1;
	    sgn = 1;
	} else {
	    a2 = 1 - 2*a;
	    sgn = -1;
	}

	p   = 1/nu;
	lg1 = ln_gamma(p);
	lg3 = ln_gamma(3*p);
	sd  = pow(2.0, p) * exp(0.5*(lg3 - lg1));
	x   = gamma_cdf_inverse(p, 2.0, a2);

	return sgn * pow(x, p) / sd;
    } else {
	return NADBL;
    }
}
