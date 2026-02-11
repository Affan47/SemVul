IndexNext(IndexScanState *node)
{
	EState	   *estate;
	ExprContext *econtext;
	ScanDirection direction;
	IndexScanDesc scandesc;
	Index		scanrelid;
	HeapTuple	tuple;
	TupleTableSlot *slot;


	estate = node->ss.ps.state;
	direction = estate->es_direction;

	if (ScanDirectionIsBackward(((IndexScan *) node->ss.ps.plan)->indexorderdir))
	{
		if (ScanDirectionIsForward(direction))
			direction = BackwardScanDirection;
		else if (ScanDirectionIsBackward(direction))
			direction = ForwardScanDirection;
	}
	scandesc = node->iss_ScanDesc;
	econtext = node->ss.ps.ps_ExprContext;
	slot = node->ss.ss_ScanTupleSlot;
	scanrelid = ((IndexScan *) node->ss.ps.plan)->scan.scanrelid;


	if (estate->es_evTuple != NULL &&
		estate->es_evTuple[scanrelid - 1] != NULL)
	{
		if (estate->es_evTupleNull[scanrelid - 1])
			return ExecClearTuple(slot);

		ExecStoreTuple(estate->es_evTuple[scanrelid - 1],
					   slot, InvalidBuffer, false);


		econtext->ecxt_scantuple = slot;

		ResetExprContext(econtext);

		if (!ExecQual(node->indexqualorig, econtext, false))
			ExecClearTuple(slot);


		estate->es_evTupleNull[scanrelid - 1] = true;

		return slot;
	}


	while ((tuple = index_getnext(scandesc, direction)) != NULL)
	{


		ExecStoreTuple(tuple,
					   slot,
					   scandesc->xs_cbuf,
					   false);


		if (scandesc->xs_recheck)
		{
			econtext->ecxt_scantuple = slot;
			ResetExprContext(econtext);
			if (!ExecQual(node->indexqualorig, econtext, false))
				continue;
		}

		return slot;
	}


	return ExecClearTuple(slot);
}
