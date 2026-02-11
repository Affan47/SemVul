build_paths_for_OR(PlannerInfo *root, RelOptInfo *rel,
				   List *clauses, List *other_clauses)
{
	List	   *result = NIL;
	List	   *all_clauses = NIL;
	ListCell   *lc;

	foreach(lc, rel->indexlist)
	{
		IndexOptInfo *index = (IndexOptInfo *) lfirst(lc);
		IndexClauseSet clauseset;
		List	   *indexpaths;
		bool		useful_predicate;


		if (!index->amhasgetbitmap)
			continue;


		useful_predicate = false;
		if (index->indpred != NIL)
		{
			if (index->predOK)
			{

			}
			else
			{

				if (all_clauses == NIL)
					all_clauses = list_concat(list_copy(clauses),
											  other_clauses);

				if (!predicate_implied_by(index->indpred, all_clauses))
					continue;

				if (!predicate_implied_by(index->indpred, other_clauses))
					useful_predicate = true;
			}
		}


		MemSet(&clauseset, 0, sizeof(clauseset));
		match_clauses_to_index(index, clauses, &clauseset);


		if (!clauseset.nonempty && !useful_predicate)
			continue;


		match_clauses_to_index(index, other_clauses, &clauseset);


		indexpaths = build_index_paths(root, rel,
									   index, &clauseset,
									   useful_predicate,
									   ST_BITMAPSCAN,
									   NULL,
									   NULL);
		result = list_concat(result, indexpaths);
	}

	return result;
}
