freeScanKeys(GinScanKey keys, uint32 nkeys, bool removeRes)
{
	uint32		i,
				j;

	if (keys == NULL)
		return;

	for (i = 0; i < nkeys; i++)
	{
		GinScanKey	key = keys + i;

		for (j = 0; j < key->nentries; j++)
		{
			if (key->scanEntry[j].buffer != InvalidBuffer)
				ReleaseBuffer(key->scanEntry[j].buffer);
			if (removeRes && key->scanEntry[j].list)
				pfree(key->scanEntry[j].list);
		}

		if (removeRes)
			pfree(key->entryRes);
		pfree(key->scanEntry);
	}

	pfree(keys);
}
