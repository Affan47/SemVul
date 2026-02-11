sort_inner_and_outer(PlannerInfo *root,
					 RelOptInfo *joinrel,
					 RelOptInfo *outerrel,
					 RelOptInfo *innerrel,
					 List *restrictlist,
					 List *mergeclause_list,
					 JoinType jointype)
{
	bool		useallclauses;
	Path	   *outer_path;
	Path	   *inner_path;
	List	   *all_pathkeys;
	ListCell   *l;


	switch (jointype)
	{
		case JOIN_INNER:
		case JOIN_LEFT:
		case JOIN_IN:
		case JOIN_UNIQUE_OUTER:
		case JOIN_UNIQUE_INNER:
			useallclauses = false;
			break;
		case JOIN_RIGHT:
		case JOIN_FULL:
			useallclauses = true;
			break;
		default:
			elog(ERROR, "unrecognized join type: %d",
				 (int) jointype);
			useallclauses = false;
			break;
	}


	outer_path = outerrel->cheapest_total_path;
	inner_path = innerrel->cheapest_total_path;
	if (jointype == JOIN_UNIQUE_OUTER)
	{
		outer_path = (Path *) create_unique_path(root, outerrel, outer_path);
		jointype = JOIN_INNER;
	}
	else if (jointype == JOIN_UNIQUE_INNER)
	{
		inner_path = (Path *) create_unique_path(root, innerrel, inner_path);
		jointype = JOIN_INNER;
	}


	all_pathkeys = make_pathkeys_for_mergeclauses(root,
												  mergeclause_list,
												  outerrel);

	foreach(l, all_pathkeys)
	{
		List	   *front_pathkey = (List *) lfirst(l);
		List	   *cur_pathkeys;
		List	   *cur_mergeclauses;
		List	   *outerkeys;
		List	   *innerkeys;
		List	   *merge_pathkeys;


		if (l != list_head(all_pathkeys))
			cur_pathkeys = lcons(front_pathkey,
								 list_delete_ptr(list_copy(all_pathkeys),
												 front_pathkey));
		else
			cur_pathkeys = all_pathkeys;


		cur_mergeclauses = find_mergeclauses_for_pathkeys(root,
														  cur_pathkeys,
														  mergeclause_list);
		Assert(cur_mergeclauses != NIL);


		if (useallclauses &&
			list_length(cur_mergeclauses) != list_length(mergeclause_list))
			continue;


		outerkeys = make_pathkeys_for_mergeclauses(root,
												   cur_mergeclauses,
												   outerrel);
		innerkeys = make_pathkeys_for_mergeclauses(root,
												   cur_mergeclauses,
												   innerrel);

		merge_pathkeys = build_join_pathkeys(root, joinrel, jointype,
											 outerkeys);


		add_path(joinrel, (Path *)
				 create_mergejoin_path(root,
									   joinrel,
									   jointype,
									   outer_path,
									   inner_path,
									   restrictlist,
									   merge_pathkeys,
									   cur_mergeclauses,
									   outerkeys,
									   innerkeys));
	}
}
