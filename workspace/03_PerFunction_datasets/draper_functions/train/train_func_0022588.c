checkNameSpaceConflicts(ParseState *pstate, List *namespace1,
						List *namespace2)
{
	ListCell   *l1;

	foreach(l1, namespace1)
	{
		RangeTblEntry *rte1 = (RangeTblEntry *) lfirst(l1);
		const char *aliasname1 = rte1->eref->aliasname;
		ListCell   *l2;

		foreach(l2, namespace2)
		{
			RangeTblEntry *rte2 = (RangeTblEntry *) lfirst(l2);

			if (strcmp(rte2->eref->aliasname, aliasname1) != 0)
				continue;
			if (rte1->rtekind == RTE_RELATION && rte1->alias == NULL &&
				rte2->rtekind == RTE_RELATION && rte2->alias == NULL &&
				rte1->relid != rte2->relid)
				continue;
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_ALIAS),
					 errmsg("table name \"%s\" specified more than once",
							aliasname1)));
		}
	}
}
