EvalOrderByExpressions(IndexScanState *node, ExprContext *econtext)
{
	int			i;
	ListCell   *l;
	MemoryContext oldContext;

	oldContext = MemoryContextSwitchTo(econtext->ecxt_per_tuple_memory);

	i = 0;
	foreach(l, node->indexorderbyorig)
	{
		ExprState  *orderby = (ExprState *) lfirst(l);

		node->iss_OrderByValues[i] = ExecEvalExpr(orderby,
												  econtext,
												  &node->iss_OrderByNulls[i],
												  NULL);
		i++;
	}

	MemoryContextSwitchTo(oldContext);
}
