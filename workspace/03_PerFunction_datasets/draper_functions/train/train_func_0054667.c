ginBuildCallback(Relation index, HeapTuple htup, Datum *values,
				 bool *isnull, bool tupleIsAlive, void *state)
{
	GinBuildState *buildstate = (GinBuildState *) state;
	MemoryContext oldCtx;
	int			i;

	oldCtx = MemoryContextSwitchTo(buildstate->tmpCtx);

	for (i = 0; i < buildstate->ginstate.origTupdesc->natts; i++)
		if (!isnull[i])
			buildstate->indtuples += ginHeapTupleBulkInsert(buildstate,
										   (OffsetNumber) (i + 1), values[i],
															&htup->t_self);


	if (buildstate->accum.allocatedMemory >= maintenance_work_mem * 1024L)
	{
		ItemPointerData *list;
		Datum		entry;
		uint32		nlist;
		OffsetNumber attnum;

		ginBeginBAScan(&buildstate->accum);
		while ((list = ginGetEntry(&buildstate->accum, &attnum, &entry, &nlist)) != NULL)
		{

			CHECK_FOR_INTERRUPTS();
			ginEntryInsert(index, &buildstate->ginstate, attnum, entry, list, nlist, TRUE);
		}

		MemoryContextReset(buildstate->tmpCtx);
		ginInitBA(&buildstate->accum);
	}

	MemoryContextSwitchTo(oldCtx);
}
