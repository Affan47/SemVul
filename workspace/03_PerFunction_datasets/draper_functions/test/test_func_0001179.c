isViewOnTempTable_walker(Node *node, void *context)
{
	if (node == NULL)
		return false;

	if (IsA(node, Query))
	{
		Query	   *query = (Query *) node;
		ListCell   *rtable;

		foreach(rtable, query->rtable)
		{
			RangeTblEntry *rte = lfirst(rtable);

			if (rte->rtekind == RTE_RELATION)
			{
				Relation	rel = heap_open(rte->relid, AccessShareLock);
				bool		istemp = rel->rd_istemp;

				heap_close(rel, AccessShareLock);
				if (istemp)
					return true;
			}
		}

		return query_tree_walker(query,
								 isViewOnTempTable_walker,
								 context,
								 QTW_IGNORE_JOINALIASES);
	}

	return expression_tree_walker(node,
								  isViewOnTempTable_walker,
								  context);
}
