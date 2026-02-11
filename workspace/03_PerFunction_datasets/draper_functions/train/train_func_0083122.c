ExecEndWindowAgg(WindowAggState *node)
{
	PlanState  *outerPlan;
	int			i;

	release_partition(node);

	ExecClearTuple(node->ss.ss_ScanTupleSlot);
	ExecClearTuple(node->first_part_slot);
	ExecClearTuple(node->agg_row_slot);
	ExecClearTuple(node->temp_slot_1);
	ExecClearTuple(node->temp_slot_2);


	ExecFreeExprContext(&node->ss.ps);
	node->ss.ps.ps_ExprContext = node->tmpcontext;
	ExecFreeExprContext(&node->ss.ps);

	for (i = 0; i < node->numaggs; i++)
	{
		if (node->peragg[i].aggcontext != node->aggcontext)
			MemoryContextDelete(node->peragg[i].aggcontext);
	}
	MemoryContextDelete(node->partcontext);
	MemoryContextDelete(node->aggcontext);

	pfree(node->perfunc);
	pfree(node->peragg);

	outerPlan = outerPlanState(node);
	ExecEndNode(outerPlan);
}
