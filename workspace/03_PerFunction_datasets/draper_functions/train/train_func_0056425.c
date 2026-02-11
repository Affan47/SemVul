create_nestloop_plan(PlannerInfo *root,
					 NestPath *best_path,
					 Plan *outer_plan,
					 Plan *inner_plan)
{
	List	   *tlist = build_relation_tlist(best_path->path.parent);
	List	   *joinrestrictclauses = best_path->joinrestrictinfo;
	List	   *joinclauses;
	List	   *otherclauses;
	NestLoop   *join_plan;


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

	join_plan = make_nestloop(tlist,
							  joinclauses,
							  otherclauses,
							  outer_plan,
							  inner_plan,
							  best_path->jointype);

	copy_path_costsize(&join_plan->join.plan, &best_path->path);

	return join_plan;
}
