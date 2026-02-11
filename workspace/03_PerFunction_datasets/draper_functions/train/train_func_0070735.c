match_eclass_clauses_to_index(PlannerInfo *root, IndexOptInfo *index,
							  IndexClauseSet *clauseset)
{
	int			indexcol;


	if (!index->rel->has_eclass_joins)
		return;

	for (indexcol = 0; indexcol < index->ncolumns; indexcol++)
	{
		ec_member_matches_arg arg;
		List	   *clauses;


		arg.index = index;
		arg.indexcol = indexcol;
		clauses = generate_implied_equalities_for_column(root,
														 index->rel,
												  ec_member_matches_indexcol,
														 (void *) &arg,
											index->rel->lateral_referencers);


		match_clauses_to_index(index, clauses, clauseset);
	}
}
