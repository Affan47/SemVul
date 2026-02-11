markTargetListOrigin(ParseState *pstate, TargetEntry *tle,
					 Var *var, int levelsup)
{
	int			netlevelsup;
	RangeTblEntry *rte;
	AttrNumber	attnum;

	if (var == NULL || !IsA(var, Var))
		return;
	netlevelsup = var->varlevelsup + levelsup;
	rte = GetRTEByRangeTablePosn(pstate, var->varno, netlevelsup);
	attnum = var->varattno;

	switch (rte->rtekind)
	{
		case RTE_RELATION:

			tle->resorigtbl = rte->relid;
			tle->resorigcol = attnum;
			break;
		case RTE_SUBQUERY:

			if (attnum != InvalidAttrNumber)
			{
				TargetEntry *ste = get_tle_by_resno(rte->subquery->targetList,
													attnum);

				if (ste == NULL || ste->resjunk)
					elog(ERROR, "subquery %s does not have attribute %d",
						 rte->eref->aliasname, attnum);
				tle->resorigtbl = ste->resorigtbl;
				tle->resorigcol = ste->resorigcol;
			}
			break;
		case RTE_JOIN:

			if (attnum != InvalidAttrNumber)
			{
				Var		   *aliasvar;

				Assert(attnum > 0 && attnum <= list_length(rte->joinaliasvars));
				aliasvar = (Var *) list_nth(rte->joinaliasvars, attnum - 1);
				markTargetListOrigin(pstate, tle, aliasvar, netlevelsup);
			}
			break;
		case RTE_FUNCTION:
		case RTE_VALUES:

			break;
		case RTE_CTE:


			if (attnum != InvalidAttrNumber && !rte->self_reference)
			{
				CommonTableExpr *cte = GetCTEForRTE(pstate, rte, netlevelsup);
				TargetEntry *ste;

				ste = get_tle_by_resno(GetCTETargetList(cte), attnum);
				if (ste == NULL || ste->resjunk)
					elog(ERROR, "subquery %s does not have attribute %d",
						 rte->eref->aliasname, attnum);
				tle->resorigtbl = ste->resorigtbl;
				tle->resorigcol = ste->resorigcol;
			}
			break;
	}
}
