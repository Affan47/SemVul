try_mergejoin_path(PlannerInfo *root,
				   RelOptInfo *joinrel,
				   Path *outer_path,
				   Path *inner_path,
				   List *pathkeys,
				   List *mergeclauses,
				   List *outersortkeys,
				   List *innersortkeys,
				   JoinType jointype,
				   JoinPathExtraData *extra)
{
	Relids		required_outer;
	JoinCostWorkspace workspace;


	required_outer = calc_non_nestloop_required_outer(outer_path,
													  inner_path);
	if (required_outer &&
		!bms_overlap(required_outer, extra->param_source_rels))
	{

		bms_free(required_outer);
		return;
	}


	required_outer = bms_add_members(required_outer, extra->extra_lateral_rels);


	if (outersortkeys &&
		pathkeys_contained_in(outersortkeys, outer_path->pathkeys))
		outersortkeys = NIL;
	if (innersortkeys &&
		pathkeys_contained_in(innersortkeys, inner_path->pathkeys))
		innersortkeys = NIL;


	initial_cost_mergejoin(root, &workspace, jointype, mergeclauses,
						   outer_path, inner_path,
						   outersortkeys, innersortkeys,
						   extra->sjinfo);

	if (add_path_precheck(joinrel,
						  workspace.startup_cost, workspace.total_cost,
						  pathkeys, required_outer))
	{
		add_path(joinrel, (Path *)
				 create_mergejoin_path(root,
									   joinrel,
									   jointype,
									   &workspace,
									   extra->sjinfo,
									   outer_path,
									   inner_path,
									   extra->restrictlist,
									   pathkeys,
									   required_outer,
									   mergeclauses,
									   outersortkeys,
									   innersortkeys));
	}
	else
	{

		bms_free(required_outer);
	}
}
