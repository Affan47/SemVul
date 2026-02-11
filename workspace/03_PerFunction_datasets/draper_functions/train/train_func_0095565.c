SeqNext(SeqScanState *node)
{
	HeapTuple	tuple;
	HeapScanDesc scandesc;
	EState	   *estate;
	ScanDirection direction;
	TupleTableSlot *slot;


	scandesc = node->ss_currentScanDesc;
	estate = node->ps.state;
	direction = estate->es_direction;
	slot = node->ss_ScanTupleSlot;


	tuple = heap_getnext(scandesc, direction);


	if (tuple)
		ExecStoreTuple(tuple,
					   slot,
					   scandesc->rs_cbuf,

					   false);
	else
		ExecClearTuple(slot);

	return slot;
}
