checkParameterValue(vector<double const *> const &par,
			    vector<unsigned int> const &len) const
{
    if (SIZE(par) < 0)
	return false;


    bool nz = SIZE(par) == 0;

    for (unsigned int i = 0; i < len[0]; ++i) {
	if (PROB(par)[i] < 0)
	    return false;
	else if (PROB(par)[i] > 0)
	    nz = true;
    }

    return nz;
}
