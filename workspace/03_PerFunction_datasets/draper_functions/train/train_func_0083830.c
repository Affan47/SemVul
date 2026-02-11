ExecInitIndexScan(IndexScan *node, EState *estate, int eflags)
{
	IndexScanState *indexstate;
	Relation	currentRelation;
	bool		relistarget;


	indexstate = makeNode(IndexScanState);
	indexstate->ss.ps.plan = (Plan *) node;
	indexstate->ss.ps.state = estate;


	ExecAssignExprContext(estate, &indexstate->ss.ps);

	indexstate->ss.ps.ps_TupFromTlist = false;


	indexstate->ss.ps.targetlist = (List *)
		ExecInitExpr((Expr *) node->scan.plan.targetlist,
					 (PlanState *) indexstate);
	indexstate->ss.ps.qual = (List *)
		ExecInitExpr((Expr *) node->scan.plan.qual,
					 (PlanState *) indexstate);
	indexstate->indexqualorig = (List *)
		ExecInitExpr((Expr *) node->indexqualorig,
					 (PlanState *) indexstate);

#define INDEXSCAN_NSLOTS 2


	ExecInitResultTupleSlot(estate, &indexstate->ss.ps);
	ExecInitScanTupleSlot(estate, &indexstate->ss);


	currentRelation = ExecOpenScanRelation(estate, node->scan.scanrelid);

	indexstate->ss.ss_currentRelation = currentRelation;
	indexstate->ss.ss_currentScanDesc = NULL;


	ExecAssignScanType(&indexstate->ss, RelationGetDescr(currentRelation));


	ExecAssignResultTypeFromTL(&indexstate->ss.ps);
	ExecAssignScanProjectionInfo(&indexstate->ss);


	if (eflags & EXEC_FLAG_EXPLAIN_ONLY)
		return indexstate;


	relistarget = ExecRelationIsTargetRelation(estate, node->scan.scanrelid);
	indexstate->iss_RelationDesc = index_open(node->indexid,
									 relistarget ? NoLock : AccessShareLock);


	indexstate->iss_RuntimeKeysReady = false;


	ExecIndexBuildScanKeys((PlanState *) indexstate,
						   indexstate->iss_RelationDesc,
						   node->indexqual,
						   node->indexstrategy,
						   node->indexsubtype,
						   &indexstate->iss_ScanKeys,
						   &indexstate->iss_NumScanKeys,
						   &indexstate->iss_RuntimeKeys,
						   &indexstate->iss_NumRuntimeKeys,
						   NULL,
						   NULL);


	if (indexstate->iss_NumRuntimeKeys != 0)
	{
		ExprContext *stdecontext = indexstate->ss.ps.ps_ExprContext;

		ExecAssignExprContext(estate, &indexstate->ss.ps);
		indexstate->iss_RuntimeContext = indexstate->ss.ps.ps_ExprContext;
		indexstate->ss.ps.ps_ExprContext = stdecontext;
	}
	else
	{
		indexstate->iss_RuntimeContext = NULL;
	}


	indexstate->iss_ScanDesc = index_beginscan(currentRelation,
											   indexstate->iss_RelationDesc,
											   estate->es_snapshot,
											   indexstate->iss_NumScanKeys,
											   indexstate->iss_ScanKeys);


	return indexstate;
}
