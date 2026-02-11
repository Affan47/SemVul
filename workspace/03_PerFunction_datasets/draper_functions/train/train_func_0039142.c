extractEntriesSU(GinState *ginstate, Datum value, int32 *nentries)
{
	bool		needUnique;
	Datum	   *entries = extractEntriesS(ginstate, value, nentries,
										  &needUnique);

	if (needUnique)
	{
		Datum	   *ptr,
				   *res;

		ptr = res = entries;

		while (ptr - entries < *nentries)
		{
			if (compareEntries(ginstate, *ptr, *res) != 0)
				*(++res) = *ptr++;
			else
				ptr++;
		}

		*nentries = res + 1 - entries;
	}

	return entries;
}
