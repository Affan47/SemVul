construct_band_list(
	__isl_keep isl_schedule *schedule, __isl_keep isl_band *parent,
	int band_nr, int *parent_active, int n_active)
{
	int i, j;
	isl_ctx *ctx = isl_schedule_get_ctx(schedule);
	int *active;
	int n_band;
	isl_band_list *list;

	n_band = 0;
	for (i = 0; i < n_active; ++i) {
		for (j = 0; j < schedule->n; ++j) {
			if (!parent_active[j])
				continue;
			if (schedule->node[j].n_band <= band_nr)
				continue;
			if (schedule->node[j].band_id[band_nr] == i) {
				n_band++;
				break;
			}
		}
	}
	for (j = 0; j < schedule->n; ++j)
		if (schedule->node[j].n_band <= band_nr)
			n_band++;

	if (n_band == 1) {
		isl_band *band;
		list = isl_band_list_alloc(ctx, n_band);
		band = construct_band(schedule, parent, band_nr,
					parent_active, n_active);
		return isl_band_list_add(list, band);
	}

	active = isl_alloc_array(ctx, int, schedule->n);
	if (!active)
		return NULL;

	list = isl_band_list_alloc(ctx, n_band);

	for (i = 0; i < n_active; ++i) {
		int n = 0;
		isl_band *band;

		for (j = 0; j < schedule->n; ++j) {
			active[j] = parent_active[j] &&
					schedule->node[j].n_band > band_nr &&
					schedule->node[j].band_id[band_nr] == i;
			if (active[j])
				n++;
		}
		if (n == 0)
			continue;

		band = construct_band(schedule, parent, band_nr, active, n);

		list = isl_band_list_add(list, band);
	}
	for (i = 0; i < schedule->n; ++i) {
		isl_band *band;
		if (!parent_active[i])
			continue;
		if (schedule->node[i].n_band > band_nr)
			continue;
		for (j = 0; j < schedule->n; ++j)
			active[j] = j == i;
		band = construct_band(schedule, parent, band_nr, active, 1);
		list = isl_band_list_add(list, band);
	}

	free(active);

	return list;
}
