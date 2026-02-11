logDensity(double x, PDFType type,
			 vector<double const *> const &par,
			 double const *lower, double const *upper) const
{
    if (x < LOWER(par) || x > UPPER(par))
	return JAGS_NEGINF;
    else if (type == PDF_PRIOR)
	return 0;
    else
	return - log(UPPER(par) - LOWER(par));
}
