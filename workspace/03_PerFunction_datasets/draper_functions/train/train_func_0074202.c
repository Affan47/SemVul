isl_union_access_info_introduce_schedule(
	__isl_take isl_union_access_info *access)
{
	isl_union_map *sm;

	if (!access)
		return NULL;

	sm = isl_union_map_reverse(access->schedule_map);
	sm = isl_union_map_range_map(sm);
	access->sink = isl_union_map_apply_range(isl_union_map_copy(sm),
						access->sink);
	access->may_source = isl_union_map_apply_range(isl_union_map_copy(sm),
						access->may_source);
	access->must_source = isl_union_map_apply_range(isl_union_map_copy(sm),
						access->must_source);
	access->schedule_map = sm;

	if (!access->sink || !access->must_source ||
	    !access->may_source || !access->schedule_map)
		return isl_union_access_info_free(access);

	return access;
}
