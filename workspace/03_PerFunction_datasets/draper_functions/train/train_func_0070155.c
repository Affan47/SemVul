query_tree_mutator(Query *query,
				   Node *(*mutator) (),
				   void *context,
				   int flags)
{
	Assert(query != NULL && IsA(query, Query));

	if (!(flags & QTW_DONT_COPY_QUERY))
	{
		Query	   *newquery;

		FLATCOPY(newquery, query, Query);
		query = newquery;
	}

	MUTATE(query->targetList, query->targetList, List *);
	MUTATE(query->returningList, query->returningList, List *);
	MUTATE(query->jointree, query->jointree, FromExpr *);
	MUTATE(query->setOperations, query->setOperations, Node *);
	MUTATE(query->havingQual, query->havingQual, Node *);
	MUTATE(query->limitOffset, query->limitOffset, Node *);
	MUTATE(query->limitCount, query->limitCount, Node *);
	query->rtable = range_table_mutator(query->rtable,
										mutator, context, flags);
	return query;
}
