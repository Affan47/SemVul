checkParameterValue(vector<double const *> const &par,
				    vector<unsigned int> const &lengths)
    const
{
    for (unsigned int i = 1; i < NCUT(lengths); ++i) {
	if (CUTPOINTS(par)[i] <= CUTPOINTS(par)[i-1])
	    return false;
    }
    return true;
}
