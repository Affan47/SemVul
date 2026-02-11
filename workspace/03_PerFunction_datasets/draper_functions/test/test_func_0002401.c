isl_union_flow_drop_schedule(
	__isl_take isl_union_flow *flow)
{
	if (!flow)
		return NULL;

	flow->must_dep = isl_union_map_factor_range(flow->must_dep);
	flow->may_dep = isl_union_map_factor_range(flow->may_dep);
	flow->must_no_source =
		isl_union_map_domain_factor_range(flow->must_no_source);
	flow->may_no_source =
		isl_union_map_domain_factor_range(flow->may_no_source);

	if (!flow->must_dep || !flow->may_dep ||
	    !flow->must_no_source || !flow->may_no_source)
		return isl_union_flow_free(flow);

	return flow;
}
