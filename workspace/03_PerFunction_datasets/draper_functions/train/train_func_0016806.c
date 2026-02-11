ExecGroup(GroupState *node)
{
	ExprContext *econtext;
	int			numCols;
	AttrNumber *grpColIdx;
	TupleTableSlot *firsttupleslot;
	TupleTableSlot *outerslot;


	if (node->grp_done)
		return NULL;
	econtext = node->ss.ps.ps_ExprContext;
	numCols = ((Group *) node->ss.ps.plan)->numCols;
	grpColIdx = ((Group *) node->ss.ps.plan)->grpColIdx;


	if (node->ss.ps.ps_TupFromTlist)
	{
		TupleTableSlot *result;
		ExprDoneCond isDone;

		result = ExecProject(node->ss.ps.ps_ProjInfo, &isDone);
		if (isDone == ExprMultipleResult)
			return result;

		node->ss.ps.ps_TupFromTlist = false;
	}


	firsttupleslot = node->ss.ss_ScanTupleSlot;


	if (TupIsNull(firsttupleslot))
	{
		outerslot = ExecProcNode(outerPlanState(node));
		if (TupIsNull(outerslot))
		{

			node->grp_done = TRUE;
			return NULL;
		}

		ExecCopySlot(firsttupleslot, outerslot);


		econtext->ecxt_outertuple = firsttupleslot;


		if (ExecQual(node->ss.ps.qual, econtext, false))
		{


			TupleTableSlot *result;
			ExprDoneCond isDone;

			result = ExecProject(node->ss.ps.ps_ProjInfo, &isDone);

			if (isDone != ExprEndResult)
			{
				node->ss.ps.ps_TupFromTlist = (isDone == ExprMultipleResult);
				return result;
			}
		}
		else
			InstrCountFiltered1(node, 1);
	}


	for (;;)
	{


		for (;;)
		{
			outerslot = ExecProcNode(outerPlanState(node));
			if (TupIsNull(outerslot))
			{

				node->grp_done = TRUE;
				return NULL;
			}


			if (!execTuplesMatch(firsttupleslot, outerslot,
								 numCols, grpColIdx,
								 node->eqfunctions,
								 econtext->ecxt_per_tuple_memory))
				break;
		}


		ExecCopySlot(firsttupleslot, outerslot);
		econtext->ecxt_outertuple = firsttupleslot;


		if (ExecQual(node->ss.ps.qual, econtext, false))
		{


			TupleTableSlot *result;
			ExprDoneCond isDone;

			result = ExecProject(node->ss.ps.ps_ProjInfo, &isDone);

			if (isDone != ExprEndResult)
			{
				node->ss.ps.ps_TupFromTlist = (isDone == ExprMultipleResult);
				return result;
			}
		}
		else
			InstrCountFiltered1(node, 1);
	}
}
