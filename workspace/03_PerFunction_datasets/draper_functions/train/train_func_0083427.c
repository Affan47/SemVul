transformAggregateCall(ParseState *pstate, Aggref *agg)
{
	int			min_varlevel;


	min_varlevel = find_minimum_var_level((Node *) agg->args);


	if (min_varlevel == 0)
	{
		if (checkExprHasAggs((Node *) agg->args))
			ereport(ERROR,
					(errcode(ERRCODE_GROUPING_ERROR),
					 errmsg("aggregate function calls may not be nested")));
	}

	if (min_varlevel < 0)
		min_varlevel = 0;
	agg->agglevelsup = min_varlevel;


	while (min_varlevel-- > 0)
		pstate = pstate->parentParseState;
	pstate->p_hasAggs = true;
}
