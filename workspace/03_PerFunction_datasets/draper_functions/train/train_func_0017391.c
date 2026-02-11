ExecReScanUnique(UniqueState *node, ExprContext *exprCtxt)
{

	ExecClearTuple(node->ps.ps_ResultTupleSlot);


	if (((PlanState *) node)->lefttree->chgParam == NULL)
		ExecReScan(((PlanState *) node)->lefttree, exprCtxt);
}
