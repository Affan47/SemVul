checkParameterDiscrete (vector<bool> const &mask) const
{

    for (unsigned int i = 0; i < 3; ++i) {
	if (mask[i] == false)
	    return false;
    }

    return true;
}
