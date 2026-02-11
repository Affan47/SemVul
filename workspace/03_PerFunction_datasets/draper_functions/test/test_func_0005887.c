extract_hull(struct isl_sched_node *src,
	struct isl_sched_node *dst)
{
	isl_set *dom, *ran;

	if (src->compressed)
		dom = isl_set_copy(src->hull);
	else
		dom = isl_set_universe(isl_space_copy(src->space));
	if (dst->compressed)
		ran = isl_set_copy(dst->hull);
	else
		ran = isl_set_universe(isl_space_copy(dst->space));

	return isl_map_from_domain_and_range(dom, ran);
}
