parseCheckAggregates(ParseState *pstate, Query *qry)
{
	List	   *groupClauses = NIL;
	bool		have_non_var_grouping;
	ListCell   *l;
	bool		hasJoinRTEs;
	PlannerInfo *root;
	Node	   *clause;


	Assert(pstate->p_hasAggs || qry->groupClause || qry->havingQual);


	if (checkExprHasAggs(qry->jointree->quals))
		ereport(ERROR,
				(errcode(ERRCODE_GROUPING_ERROR),
				 errmsg("aggregates not allowed in WHERE clause")));
	if (checkExprHasAggs((Node *) qry->jointree->fromlist))
		ereport(ERROR,
				(errcode(ERRCODE_GROUPING_ERROR),
				 errmsg("aggregates not allowed in JOIN conditions")));


	foreach(l, qry->groupClause)
	{
		GroupClause *grpcl = (GroupClause *) lfirst(l);
		Node	   *expr;

		expr = get_sortgroupclause_expr(grpcl, qry->targetList);
		if (expr == NULL)
			continue;
		if (checkExprHasAggs(expr))
			ereport(ERROR,
					(errcode(ERRCODE_GROUPING_ERROR),
					 errmsg("aggregates not allowed in GROUP BY clause")));
		groupClauses = lcons(expr, groupClauses);
	}


	hasJoinRTEs = false;
	foreach(l, pstate->p_rtable)
	{
		RangeTblEntry *rte = (RangeTblEntry *) lfirst(l);

		if (rte->rtekind == RTE_JOIN)
		{
			hasJoinRTEs = true;
			break;
		}
	}


	if (hasJoinRTEs)
	{
		root = makeNode(PlannerInfo);
		root->parse = qry;
		root->hasJoinRTEs = true;

		groupClauses = (List *) flatten_join_alias_vars(root,
													  (Node *) groupClauses);
	}
	else
		root = NULL;


	have_non_var_grouping = false;
	foreach(l, groupClauses)
	{
		if (!IsA((Node *) lfirst(l), Var))
		{
			have_non_var_grouping = true;
			break;
		}
	}


	clause = (Node *) qry->targetList;
	if (hasJoinRTEs)
		clause = flatten_join_alias_vars(root, clause);
	check_ungrouped_columns(clause, pstate,
							groupClauses, have_non_var_grouping);

	clause = (Node *) qry->havingQual;
	if (hasJoinRTEs)
		clause = flatten_join_alias_vars(root, clause);
	check_ungrouped_columns(clause, pstate,
							groupClauses, have_non_var_grouping);
}
