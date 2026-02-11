ginHeapTupleFastCollect(GinState *ginstate,
						GinTupleCollector *collector,
						OffsetNumber attnum, Datum value, bool isNull,
						ItemPointer ht_ctid)
{
	Datum	   *entries;
	GinNullCategory *categories;
	int32		i,
				nentries;


	entries = ginExtractEntries(ginstate, attnum, value, isNull,
								&nentries, &categories);


	if (collector->tuples == NULL)
	{
		collector->lentuples = nentries * ginstate->origTupdesc->natts;
		collector->tuples = (IndexTuple *) palloc(sizeof(IndexTuple) * collector->lentuples);
	}

	while (collector->ntuples + nentries > collector->lentuples)
	{
		collector->lentuples *= 2;
		collector->tuples = (IndexTuple *) repalloc(collector->tuples,
								  sizeof(IndexTuple) * collector->lentuples);
	}


	for (i = 0; i < nentries; i++)
	{
		IndexTuple	itup;

		itup = GinFormTuple(ginstate, attnum, entries[i], categories[i],
							NULL, 0, true);
		itup->t_tid = *ht_ctid;
		collector->tuples[collector->ntuples++] = itup;
		collector->sumsize += IndexTupleSize(itup);
	}
}
