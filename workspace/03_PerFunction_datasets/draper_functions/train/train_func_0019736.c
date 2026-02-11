ksOutput(const KeySet *ks, FILE *stream, option_t options)
{
	Key	*key;
	KeySet *cks = ksDup (ks);
	size_t size = 0;

	if (ksNeedSort(cks)) ksSort (cks);
	ksRewind (cks);

	if (KDB_O_HEADER & options) {
		fprintf(stream,"Output keyset of size %d\n", (int)ksGetSize(cks));
	}
	while ( (key = ksNext(cks)) != NULL)
	{
		if (options & KDB_O_SHOWINDICES) fprintf(stream, "[%d] ", (int)size);
		keyOutput (key,stream,options);
		size ++;
	}

	ksDel (cks);
	return 1;
}
