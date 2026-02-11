get
	(
	int i,
	size_t& len
	)
	{
	if (i >= 0 && i < entries.size())
		{
		if (!entries[i])
			{
			entries[i] = flex->retrieve(i, len);
			lengths[i] = len;
			}
		len = lengths[i];
		return entries[i];
		}
	else
		return 0;
	}
