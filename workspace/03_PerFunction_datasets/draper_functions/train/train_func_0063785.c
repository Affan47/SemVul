InstallTimeZoneAbbrevs(tzEntry *abbrevs, int n)
{
	datetkn    *newtbl;
	int			i;


	newtbl = (datetkn *) MemoryContextAlloc(TopMemoryContext,
											n * sizeof(datetkn));
	for (i = 0; i < n; i++)
	{
		strncpy(newtbl[i].token, abbrevs[i].abbrev, TOKMAXLEN);
		newtbl[i].type = abbrevs[i].is_dst ? DTZ : TZ;
		TOVAL(&newtbl[i], abbrevs[i].offset / 60);
	}


	Assert(CheckDateTokenTable("timezone offset", newtbl, n));


	if (timezonetktbl)
		pfree(timezonetktbl);
	timezonetktbl = newtbl;
	sztimezonetktbl = n;


	for (i = 0; i < MAXDATEFIELDS; i++)
		datecache[i] = NULL;
}
