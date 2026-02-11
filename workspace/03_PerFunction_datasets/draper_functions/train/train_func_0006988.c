create_node_scaled(
	__isl_take isl_union_map *executed,
	__isl_take isl_basic_set *bounds, __isl_take isl_set *domain,
	__isl_take isl_ast_build *build)
{
	int depth;
	int degenerate, eliminated;
	isl_basic_set *hull;
	isl_basic_set *enforced;
	isl_set *guard, *hoisted;
	isl_ast_node *node = NULL;
	isl_ast_graft *graft;
	isl_ast_graft_list *children;
	isl_ast_build *sub_build;
	isl_ast_build *body_build;

	domain = isl_ast_build_eliminate_divs(build, domain);
	domain = isl_set_detect_equalities(domain);
	hull = isl_set_unshifted_simple_hull(isl_set_copy(domain));
	bounds = isl_basic_set_intersect(bounds, hull);
	build = isl_ast_build_set_executed(build, isl_union_map_copy(executed));

	depth = isl_ast_build_get_depth(build);
	sub_build = isl_ast_build_copy(build);
	sub_build = isl_ast_build_set_loop_bounds(sub_build,
						isl_basic_set_copy(bounds));
	degenerate = isl_ast_build_has_value(sub_build);
	eliminated = isl_ast_build_has_affine_value(sub_build, depth);
	if (degenerate < 0 || eliminated < 0)
		executed = isl_union_map_free(executed);
	if (eliminated)
		executed = plug_in_values(executed, sub_build);
	else
		node = create_for(build, degenerate);

	body_build = isl_ast_build_copy(sub_build);
	body_build = isl_ast_build_increase_depth(body_build);
	if (!eliminated)
		node = before_each_for(node, body_build);
	children = generate_next_level(executed,
				    isl_ast_build_copy(body_build));

	enforced = extract_shared_enforced(children, build);
	guard = extract_pending(sub_build, enforced);
	hoisted = isl_ast_graft_list_extract_hoistable_guard(children, build);
	if (isl_set_n_basic_set(hoisted) > 1)
		children = isl_ast_graft_list_gist_guards(children,
						    isl_set_copy(hoisted));
	guard = isl_set_intersect(guard, hoisted);
	if (!eliminated)
		guard = add_implied_guards(guard, degenerate, bounds, build);

	graft = isl_ast_graft_alloc_from_children(children,
			    isl_set_copy(guard), enforced, build, sub_build);

	if (!degenerate)
		bounds = isl_ast_build_compute_gist_basic_set(build, bounds);
	if (!eliminated) {
		isl_ast_build *for_build;

		graft = isl_ast_graft_insert_for(graft, node);
		for_build = isl_ast_build_copy(build);
		for_build = isl_ast_build_replace_pending_by_guard(for_build,
							isl_set_copy(guard));
		if (degenerate)
			graft = refine_degenerate(graft, for_build, sub_build);
		else
			graft = refine_generic(graft, bounds,
					domain, for_build);
		isl_ast_build_free(for_build);
	}
	isl_set_free(guard);
	if (!eliminated)
		graft = after_each_for(graft, body_build);

	isl_ast_build_free(body_build);
	isl_ast_build_free(sub_build);
	isl_ast_build_free(build);
	isl_basic_set_free(bounds);
	isl_set_free(domain);

	return graft;
}
