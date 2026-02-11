ExecReScanGroup(GroupState *node, ExprContext *exprCtxt)
{
	node->grp_done = FALSE;

	ExecClearTuple(node->ss.ss_ScanTupleSlot);

	if (((PlanState *) node)->lefttree &&
		((PlanState *) node)->lefttree->chgParam == NULL)
		ExecReScan(((PlanState *) node)->lefttree, exprCtxt);
}
