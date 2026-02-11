ExecMaterialReScan(MaterialState *node, ExprContext *exprCtxt)
{
	ExecClearTuple(node->ss.ps.ps_ResultTupleSlot);

	if (node->randomAccess)
	{


		if (!node->tuplestorestate)
			return;


		if (((PlanState *) node)->lefttree->chgParam != NULL)
		{
			tuplestore_end((Tuplestorestate *) node->tuplestorestate);
			node->tuplestorestate = NULL;
			node->eof_underlying = false;
		}
		else
			tuplestore_rescan((Tuplestorestate *) node->tuplestorestate);
	}
	else
	{


		if (((PlanState *) node)->lefttree->chgParam == NULL)
			ExecReScan(((PlanState *) node)->lefttree, exprCtxt);
		node->eof_underlying = false;
	}
}
