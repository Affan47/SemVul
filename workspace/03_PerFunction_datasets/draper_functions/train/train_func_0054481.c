ExecEndBitmapHeapScan(BitmapHeapScanState *node)
{
	Relation	relation;
	HeapScanDesc scanDesc;


	relation = node->ss.ss_currentRelation;
	scanDesc = node->ss.ss_currentScanDesc;


	ExecFreeExprContext(&node->ss.ps);


	ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);
	ExecClearTuple(node->ss.ss_ScanTupleSlot);


	ExecEndNode(outerPlanState(node));


	if (node->tbmiterator)
		tbm_end_iterate(node->tbmiterator);
	if (node->prefetch_iterator)
		tbm_end_iterate(node->prefetch_iterator);
	if (node->tbm)
		tbm_free(node->tbm);


	heap_endscan(scanDesc);


	ExecCloseScanRelation(relation);
}
