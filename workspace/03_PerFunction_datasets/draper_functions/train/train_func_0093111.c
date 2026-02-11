name() const
{
    static const string nullstring;
    if (lfunc)
	return lfunc->name();
    else if (sfunc)
	return sfunc->name();
    else if (vfunc)
	return vfunc->name();
    else if (afunc)
	return afunc->name();
    else
	return nullstring;
}
