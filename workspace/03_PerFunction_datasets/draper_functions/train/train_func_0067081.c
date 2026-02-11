ajCharGetfilter(const char *txt)
{
    char *ret;
    const char* cp;

    ret = AJALLOC0(256);

    if(!txt)
	return ret;

    if(!*txt)
        return ret;

    cp = txt;

    while (*cp)
    {
        ret[((int)*cp++)] = 1;
    }

    return ret;
}
