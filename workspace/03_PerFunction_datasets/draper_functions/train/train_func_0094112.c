kdbGetKey(KDB *handle, Key * dest)
{
	Key * source;
	KeySet *ks = 0;
	ssize_t ret;

	if (!handle || !dest) return -1;

	ks = ksNew(0);

	ret = kdbGetHelper (handle, ks, dest, KDB_O_INACTIVE);

	if (ret == -1)
	{
		ksDel (ks);

		return -1;
	}

	source = ksLookup (ks, dest, 0);

	if (!source)
	{
		ksDel (ks);

		return -1;
	}

	if (keyCopy(dest, source) == -1)
	{
		ksDel (ks);
		return -1;
	}

	ksDel (ks);
	return 0;
}
