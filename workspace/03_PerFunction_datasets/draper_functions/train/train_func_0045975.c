typicalValue(double *x, unsigned int length,
			 vector<double const *> const &par,
			 vector<vector<unsigned int> > const &dims,
			 double const *lower, double const *upper) const
{


    if (!inverse_spd(x, SCALE(par), NROW(dims))) {
	throwDistError(this, "Inverse failed in typicalValue");
    }
    for (unsigned int i = 0; i < length; ++i) {
	x[i] *= DF(par);
    }
}
