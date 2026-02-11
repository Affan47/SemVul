ExecBitmapHeapReScan(BitmapHeapScanState *node, ExprContext *exprCtxt)
{
	EState	   *estate;
	Index		scanrelid;

	estate = node->ss.ps.state;
	scanrelid = ((BitmapHeapScan *) node->ss.ps.plan)->scan.scanrelid;

	node->ss.ps.ps_TupFromTlist = false;


	if (exprCtxt != NULL)
	{
		ExprContext *stdecontext;

		stdecontext = node->ss.ps.ps_ExprContext;
		stdecontext->ecxt_outertuple = exprCtxt->ecxt_outertuple;
	}


	if (estate->es_evTuple != NULL &&
		estate->es_evTuple[scanrelid - 1] != NULL)
	{
		estate->es_evTupleNull[scanrelid - 1] = false;
	}


	heap_rescan(node->ss.ss_currentScanDesc, NULL);

	if (node->tbm)
		tbm_free(node->tbm);
	node->tbm = NULL;
	node->tbmres = NULL;


	ExecReScan(outerPlanState(node), exprCtxt);
}
