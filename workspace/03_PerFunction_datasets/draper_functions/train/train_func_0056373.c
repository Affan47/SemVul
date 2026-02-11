setSortType(const String& sorttype)
{
    static const struct
    {
	char		*typest;
	SortType	type;
    }
    sorttypes[] =
    {
	{"score", SortByScore},
	{"date", SortByTime},
	{"time", SortByTime},
        {"title", SortByTitle},
        {"id", SortByID}
    };
    int		i = 0;
    const char	*st = sorttype;
    if (st && *st)
    {
	if (mystrncasecmp("rev", st, 3) == 0)
	    st += 3;
	for (i = sizeof(sorttypes)/sizeof(sorttypes[0]); --i >= 0; )
	{
	    if (mystrcasecmp(sorttypes[i].typest, st) == 0)
	    {
		mySortType = sorttypes[i].type;
		return 1;
	    }
	}
	return 0;
    }
    else
    {

      mySortType = SortByScore;
      return 1;
    }
}
