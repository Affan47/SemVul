extractEntriesS(GinState *ginstate, Datum value, int32 *nentries,
				bool *needUnique)
{
	Datum	   *entries;

	entries = (Datum *) DatumGetPointer(FunctionCall2(
												   &ginstate->extractValueFn,
													  value,
													PointerGetDatum(nentries)
													  ));

	if (entries == NULL)
		*nentries = 0;

	*needUnique = FALSE;
	if (*nentries > 1)
	{
		cmpEntriesData arg;

		arg.cmpDatumFunc = &ginstate->compareFn;
		arg.needUnique = needUnique;
		qsort_arg(entries, *nentries, sizeof(Datum),
				  (qsort_arg_comparator) cmpEntries, (void *) &arg);
	}

	return entries;
}
