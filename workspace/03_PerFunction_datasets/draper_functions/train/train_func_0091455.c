count()
    const
{
    setgrent();
    long n = 0;
    for (;;)
    {
	struct group *gr = getgrent();
	if (!gr)
	    break;
	++n;
    }
    return rpt_value_integer::create(n);
}
