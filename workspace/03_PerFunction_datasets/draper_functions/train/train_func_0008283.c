QueryRewrite(Query *parsetree)
{
	List	   *querylist;
	List	   *results = NIL;
	ListCell   *l;
	CmdType		origCmdType;
	bool		foundOriginalQuery;
	Query	   *lastInstead;


	querylist = RewriteQuery(parsetree, NIL);


	foreach(l, querylist)
	{
		Query	   *query = (Query *) lfirst(l);

		query = fireRIRrules(query, NIL);


		if (query->resultRelation)
		{
			RangeTblEntry *rte = rt_fetch(query->resultRelation,
										  query->rtable);

			if (rte->rtekind == RTE_SUBQUERY)
			{
				switch (query->commandType)
				{
					case CMD_INSERT:
						ereport(ERROR,
								(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
								 errmsg("cannot insert into a view"),
								 errhint("You need an unconditional ON INSERT DO INSTEAD rule.")));
						break;
					case CMD_UPDATE:
						ereport(ERROR,
								(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
								 errmsg("cannot update a view"),
								 errhint("You need an unconditional ON UPDATE DO INSTEAD rule.")));
						break;
					case CMD_DELETE:
						ereport(ERROR,
								(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
								 errmsg("cannot delete from a view"),
								 errhint("You need an unconditional ON DELETE DO INSTEAD rule.")));
						break;
					default:
						elog(ERROR, "unrecognized commandType: %d",
							 (int) query->commandType);
						break;
				}
			}
		}

		results = lappend(results, query);
	}


	origCmdType = parsetree->commandType;
	foundOriginalQuery = false;
	lastInstead = NULL;

	foreach(l, results)
	{
		Query	   *query = (Query *) lfirst(l);

		if (query->querySource == QSRC_ORIGINAL)
		{
			Assert(query->canSetTag);
			Assert(!foundOriginalQuery);
			foundOriginalQuery = true;
#ifndef USE_ASSERT_CHECKING
			break;
#endif
		}
		else
		{
			Assert(!query->canSetTag);
			if (query->commandType == origCmdType &&
				(query->querySource == QSRC_INSTEAD_RULE ||
				 query->querySource == QSRC_QUAL_INSTEAD_RULE))
				lastInstead = query;
		}
	}

	if (!foundOriginalQuery && lastInstead != NULL)
		lastInstead->canSetTag = true;

	return results;
}
