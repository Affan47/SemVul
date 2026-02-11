match_join_clauses_to_index(PlannerInfo *root,
							RelOptInfo *rel, IndexOptInfo *index,
							IndexClauseSet *clauseset,
							List **joinorclauses)
{
	ListCell   *lc;


	foreach(lc, rel->joininfo)
	{
		RestrictInfo *rinfo = (RestrictInfo *) lfirst(lc);


		if (!join_clause_is_movable_to(rinfo, rel))
			continue;


		if (restriction_is_or_clause(rinfo))
			*joinorclauses = lappend(*joinorclauses, rinfo);
		else
			match_clause_to_index(index, rinfo, clauseset);
	}
}
