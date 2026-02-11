isl_union_access_info_set_schedule(
	__isl_take isl_union_access_info *access,
	__isl_take isl_schedule *schedule)
{
	if (!access || !schedule)
		goto error;

	access->schedule_map = isl_union_map_free(access->schedule_map);
	isl_schedule_free(access->schedule);
	access->schedule = schedule;

	return access;
error:
	isl_union_access_info_free(access);
	isl_schedule_free(schedule);
	return NULL;
}
