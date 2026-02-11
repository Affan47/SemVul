findTargetlistEntrySQL92(ParseState *pstate, Node *node, List **tlist,
						 int clause)
{
	ListCell   *tl;


	if (IsA(node, ColumnRef) &&
		list_length(((ColumnRef *) node)->fields) == 1 &&
		IsA(linitial(((ColumnRef *) node)->fields), String))
	{
		char	   *name = strVal(linitial(((ColumnRef *) node)->fields));
		int			location = ((ColumnRef *) node)->location;

		if (clause == GROUP_CLAUSE)
		{


			if (colNameToVar(pstate, name, true, location) != NULL)
				name = NULL;
		}

		if (name != NULL)
		{
			TargetEntry *target_result = NULL;

			foreach(tl, *tlist)
			{
				TargetEntry *tle = (TargetEntry *) lfirst(tl);

				if (!tle->resjunk &&
					strcmp(tle->resname, name) == 0)
				{
					if (target_result != NULL)
					{
						if (!equal(target_result->expr, tle->expr))
							ereport(ERROR,
									(errcode(ERRCODE_AMBIGUOUS_COLUMN),


									 errmsg("%s \"%s\" is ambiguous",
											clauseText[clause], name),
									 parser_errposition(pstate, location)));
					}
					else
						target_result = tle;

				}
			}
			if (target_result != NULL)
				return target_result;
		}
	}
	if (IsA(node, A_Const))
	{
		Value	   *val = &((A_Const *) node)->val;
		int			location = ((A_Const *) node)->location;
		int			targetlist_pos = 0;
		int			target_pos;

		if (!IsA(val, Integer))
			ereport(ERROR,
					(errcode(ERRCODE_SYNTAX_ERROR),

					 errmsg("non-integer constant in %s",
							clauseText[clause]),
					 parser_errposition(pstate, location)));

		target_pos = intVal(val);
		foreach(tl, *tlist)
		{
			TargetEntry *tle = (TargetEntry *) lfirst(tl);

			if (!tle->resjunk)
			{
				if (++targetlist_pos == target_pos)
					return tle;
			}
		}
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),

				 errmsg("%s position %d is not in select list",
						clauseText[clause], target_pos),
				 parser_errposition(pstate, location)));
	}


	return findTargetlistEntrySQL99(pstate, node, tlist);
}
