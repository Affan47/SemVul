ginHeapTupleBulkInsert(GinBuildState *buildstate, OffsetNumber attnum, Datum value, ItemPointer heapptr)
{
	Datum	   *entries;
	int32		nentries;
	MemoryContext oldCtx;

	oldCtx = MemoryContextSwitchTo(buildstate->funcCtx);
	entries = extractEntriesSU(buildstate->accum.ginstate, attnum, value, &nentries);
	MemoryContextSwitchTo(oldCtx);

	if (nentries == 0)

		return 0;

	ginInsertRecordBA(&buildstate->accum, heapptr, attnum, entries, nentries);

	MemoryContextReset(buildstate->funcCtx);

	return nentries;
}
