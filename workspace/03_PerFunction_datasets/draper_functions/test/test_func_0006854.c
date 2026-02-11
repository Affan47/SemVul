create_nestloop_plan(PlannerInfo *root,
					 NestPath *best_path,
					 Plan *outer_plan,
					 Plan *inner_plan)
{
	NestLoop   *join_plan;
	List	   *tlist = build_relation_tlist(best_path->path.parent);
	List	   *joinrestrictclauses = best_path->joinrestrictinfo;
	List	   *joinclauses;
	List	   *otherclauses;
	Relids		outerrelids;
	List	   *nestParams;
	ListCell   *cell;
	ListCell   *prev;
	ListCell   *next;


	joinrestrictclauses =
		select_nonredundant_join_clauses(root,
										 joinrestrictclauses,
										 best_path->innerjoinpath);


	joinrestrictclauses = order_qual_clauses(root, joinrestrictclauses);


	if (IS_OUTER_JOIN(best_path->jointype))
	{
		extract_actual_join_clauses(joinrestrictclauses,
									&joinclauses, &otherclauses);
	}
	else
	{

		joinclauses = extract_actual_clauses(joinrestrictclauses, false);
		otherclauses = NIL;
	}


	outerrelids = best_path->outerjoinpath->parent->relids;
	nestParams = NIL;
	prev = NULL;
	for (cell = list_head(root->curOuterParams); cell; cell = next)
	{
		NestLoopParam *nlp = (NestLoopParam *) lfirst(cell);

		next = lnext(cell);
		if (bms_is_member(nlp->paramval->varno, outerrelids))
		{
			root->curOuterParams = list_delete_cell(root->curOuterParams,
													cell, prev);
			nestParams = lappend(nestParams, nlp);
		}
		else
			prev = cell;
	}

	join_plan = make_nestloop(tlist,
							  joinclauses,
							  otherclauses,
							  nestParams,
							  outer_plan,
							  inner_plan,
							  best_path->jointype);

	copy_path_costsize(&join_plan->join.plan, &best_path->path);

	return join_plan;
}
