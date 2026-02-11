construct_forest(
	__isl_keep isl_schedule *schedule)
{
	int i;
	isl_ctx *ctx = isl_schedule_get_ctx(schedule);
	isl_band_list *forest;
	int *active;

	active = isl_alloc_array(ctx, int, schedule->n);
	if (!active)
		return NULL;

	for (i = 0; i < schedule->n; ++i)
		active[i] = 1;

	forest = construct_band_list(schedule, NULL, 0, active, schedule->n);

	free(active);

	return forest;
}
