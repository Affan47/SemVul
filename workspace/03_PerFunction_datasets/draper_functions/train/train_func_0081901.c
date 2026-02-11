logDensity(double const *x, unsigned int length, PDFType type,
			 vector<double const *> const &par,
			 vector<vector<unsigned int> > const &dims,
			 double const *lower, double const *upper) const
{
    double const *scale = SCALE(par);
    unsigned int p = NROW(dims);

    double loglik = (DF(par) - p - 1) * logdet(x, p);
    for (unsigned int i = 0; i < length; ++i) {
	loglik -= scale[i] * x[i];
    }

    if (type != PDF_PRIOR) {

	loglik += DF(par) * logdet(scale, p) -  DF(par) * p * log(2.0) -
	    2 * log_multigamma(DF(par), p);
    }

    return loglik/2;
}
