show_sort_keys_common(PlanState *planstate, int nkeys, AttrNumber *keycols,
					  List *ancestors, ExplainState *es)
{
	Plan	   *plan = planstate->plan;
	List	   *context;
	List	   *result = NIL;
	bool		useprefix;
	int			keyno;
	char	   *exprstr;

	if (nkeys <= 0)
		return;


	context = deparse_context_for_planstate((Node *) planstate,
											ancestors,
											es->rtable);
	useprefix = (list_length(es->rtable) > 1 || es->verbose);

	for (keyno = 0; keyno < nkeys; keyno++)
	{

		AttrNumber	keyresno = keycols[keyno];
		TargetEntry *target = get_tle_by_resno(plan->targetlist,
											   keyresno);

		if (!target)
			elog(ERROR, "no tlist entry for key %d", keyresno);

		exprstr = deparse_expression((Node *) target->expr, context,
									 useprefix, true);
		result = lappend(result, exprstr);
	}

	ExplainPropertyList("Sort Key", result, es);
}
