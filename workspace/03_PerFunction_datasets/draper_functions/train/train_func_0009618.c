ExecInitBitmapIndexScan(BitmapIndexScan *node, EState *estate, int eflags)
{
	BitmapIndexScanState *indexstate;
	bool		relistarget;


	Assert(!(eflags & (EXEC_FLAG_BACKWARD | EXEC_FLAG_MARK)));


	indexstate = makeNode(BitmapIndexScanState);
	indexstate->ss.ps.plan = (Plan *) node;
	indexstate->ss.ps.state = estate;


	indexstate->biss_result = NULL;


	indexstate->ss.ss_currentRelation = NULL;
	indexstate->ss.ss_currentScanDesc = NULL;


	if (eflags & EXEC_FLAG_EXPLAIN_ONLY)
		return indexstate;


	relistarget = ExecRelationIsTargetRelation(estate, node->scan.scanrelid);
	indexstate->biss_RelationDesc = index_open(node->indexid,
									 relistarget ? NoLock : AccessShareLock);


	indexstate->biss_RuntimeKeysReady = false;


	ExecIndexBuildScanKeys((PlanState *) indexstate,
						   indexstate->biss_RelationDesc,
						   node->scan.scanrelid,
						   node->indexqual,
						   &indexstate->biss_ScanKeys,
						   &indexstate->biss_NumScanKeys,
						   &indexstate->biss_RuntimeKeys,
						   &indexstate->biss_NumRuntimeKeys,
						   &indexstate->biss_ArrayKeys,
						   &indexstate->biss_NumArrayKeys);


	if (indexstate->biss_NumRuntimeKeys != 0 ||
		indexstate->biss_NumArrayKeys != 0)
	{
		ExprContext *stdecontext = indexstate->ss.ps.ps_ExprContext;

		ExecAssignExprContext(estate, &indexstate->ss.ps);
		indexstate->biss_RuntimeContext = indexstate->ss.ps.ps_ExprContext;
		indexstate->ss.ps.ps_ExprContext = stdecontext;
	}
	else
	{
		indexstate->biss_RuntimeContext = NULL;
	}


	indexstate->biss_ScanDesc =
		index_beginscan_bitmap(indexstate->biss_RelationDesc,
							   estate->es_snapshot,
							   indexstate->biss_NumScanKeys,
							   indexstate->biss_ScanKeys);


	return indexstate;
}
