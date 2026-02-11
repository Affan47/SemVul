remove_subr(int e)
{
    if (e < 0 || e >= _subrs.size())
	return false;
    delete _subrs[e];
    _subrs[e] = 0;
    return true;
}
