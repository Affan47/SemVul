lookup(IPAddress a, EtherAddress &ena) const
{
    int best = -1;
    for (int i = 0; i < _v.size(); i++)
	if (a.matches_prefix(_v[i].dst, _v[i].mask)) {
	    if (best < 0 || _v[i].mask.mask_as_specific(_v[best].mask))
		best = i;
	}

    if (best < 0)
	return false;
    else {
	ena = _v[best].ena;
	return true;
    }
}
