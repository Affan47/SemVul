support(double *lower, double *upper, unsigned int length,
	           vector<double const *> const &par,
	           vector<unsigned int> const &lengths) const
{
    if (length != 1)
	throwLogicError("Invalid length in DCat::support");

    *lower = 1;
    *upper = NCAT(lengths);
}
