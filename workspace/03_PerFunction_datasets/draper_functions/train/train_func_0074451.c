TidNext(TidScanState *node)
{
	EState	   *estate;
	ScanDirection direction;
	Snapshot	snapshot;
	Relation	heapRelation;
	HeapTuple	tuple;
	TupleTableSlot *slot;
	Index		scanrelid;
	Buffer		buffer = InvalidBuffer;
	ItemPointerData *tidList;
	int			numTids;
	bool		bBackward;


	estate = node->ss.ps.state;
	direction = estate->es_direction;
	snapshot = estate->es_snapshot;
	heapRelation = node->ss.ss_currentRelation;
	slot = node->ss.ss_ScanTupleSlot;
	scanrelid = ((TidScan *) node->ss.ps.plan)->scan.scanrelid;


	if (estate->es_evTuple != NULL &&
		estate->es_evTuple[scanrelid - 1] != NULL)
	{
		if (estate->es_evTupleNull[scanrelid - 1])
			return ExecClearTuple(slot);


		ExecStoreTuple(estate->es_evTuple[scanrelid - 1],
					   slot, InvalidBuffer, false);


		estate->es_evTupleNull[scanrelid - 1] = true;
		return slot;
	}


	if (node->tss_TidList == NULL)
		TidListCreate(node);

	tidList = node->tss_TidList;
	numTids = node->tss_NumTids;

	tuple = &(node->tss_htup);


	bBackward = ScanDirectionIsBackward(direction);
	if (bBackward)
	{
		if (node->tss_TidPtr < 0)
		{

			node->tss_TidPtr = numTids - 1;
		}
		else
			node->tss_TidPtr--;
	}
	else
	{
		if (node->tss_TidPtr < 0)
		{

			node->tss_TidPtr = 0;
		}
		else
			node->tss_TidPtr++;
	}

	while (node->tss_TidPtr >= 0 && node->tss_TidPtr < numTids)
	{
		tuple->t_self = tidList[node->tss_TidPtr];


		if (node->tss_isCurrentOf)
			heap_get_latest_tid(heapRelation, snapshot, &tuple->t_self);

		if (heap_fetch(heapRelation, snapshot, tuple, &buffer, false, NULL))
		{


			ExecStoreTuple(tuple,
						   slot,
						   buffer,
						   false);


			ReleaseBuffer(buffer);

			return slot;
		}

		if (bBackward)
			node->tss_TidPtr--;
		else
			node->tss_TidPtr++;
	}


	return ExecClearTuple(slot);
}
