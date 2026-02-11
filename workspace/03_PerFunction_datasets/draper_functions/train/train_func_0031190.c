set
	(
	int i,
	char *newentry,
	int entlen
	)
	{
	if (i < 0 || i > entries.size())
		return;
	if (i == entries.size())
		{
		entries.push_back(newentry);
		lengths.push_back(entlen);
		}
	else
		{
		delete entries[i];
		entries[i] = newentry;
		lengths[i] = entlen;
		}
	}
