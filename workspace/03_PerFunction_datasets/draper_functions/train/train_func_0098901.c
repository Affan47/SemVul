ExecProcNode(PlanState *node)
{
	TupleTableSlot *result;

	CHECK_FOR_INTERRUPTS();

	if (node->chgParam != NULL)
		ExecReScan(node, NULL);

	if (node->instrument)
		InstrStartNode(node->instrument);

	switch (nodeTag(node))
	{


		case T_ResultState:
			result = ExecResult((ResultState *) node);
			break;

		case T_AppendState:
			result = ExecAppend((AppendState *) node);
			break;


		case T_SeqScanState:
			result = ExecSeqScan((SeqScanState *) node);
			break;

		case T_IndexScanState:
			result = ExecIndexScan((IndexScanState *) node);
			break;


		case T_BitmapHeapScanState:
			result = ExecBitmapHeapScan((BitmapHeapScanState *) node);
			break;

		case T_TidScanState:
			result = ExecTidScan((TidScanState *) node);
			break;

		case T_SubqueryScanState:
			result = ExecSubqueryScan((SubqueryScanState *) node);
			break;

		case T_FunctionScanState:
			result = ExecFunctionScan((FunctionScanState *) node);
			break;

		case T_ValuesScanState:
			result = ExecValuesScan((ValuesScanState *) node);
			break;


		case T_NestLoopState:
			result = ExecNestLoop((NestLoopState *) node);
			break;

		case T_MergeJoinState:
			result = ExecMergeJoin((MergeJoinState *) node);
			break;

		case T_HashJoinState:
			result = ExecHashJoin((HashJoinState *) node);
			break;


		case T_MaterialState:
			result = ExecMaterial((MaterialState *) node);
			break;

		case T_SortState:
			result = ExecSort((SortState *) node);
			break;

		case T_GroupState:
			result = ExecGroup((GroupState *) node);
			break;

		case T_AggState:
			result = ExecAgg((AggState *) node);
			break;

		case T_UniqueState:
			result = ExecUnique((UniqueState *) node);
			break;

		case T_HashState:
			result = ExecHash((HashState *) node);
			break;

		case T_SetOpState:
			result = ExecSetOp((SetOpState *) node);
			break;

		case T_LimitState:
			result = ExecLimit((LimitState *) node);
			break;

		default:
			elog(ERROR, "unrecognized node type: %d", (int) nodeTag(node));
			result = NULL;
			break;
	}

	if (node->instrument)
		InstrStopNode(node->instrument, TupIsNull(result) ? 0.0 : 1.0);

	return result;
}
