compute_flow_schedule(
	__isl_take isl_union_access_info *access)
{
	struct isl_compute_flow_schedule_data data = { access };
	int i, n;
	isl_ctx *ctx;
	isl_union_flow *flow;

	ctx = isl_union_access_info_get_ctx(access);

	data.n_sink = 0;
	data.n_source = 0;
	if (isl_schedule_foreach_schedule_node(access->schedule,
						&count_sink_source, &data) < 0)
		goto error;

	n = data.n_sink + data.n_source;
	data.sink = isl_calloc_array(ctx, struct isl_scheduled_access, n);
	if (n && !data.sink)
		goto error;
	data.source = data.sink + data.n_sink;

	data.n_sink = 0;
	data.n_source = 0;
	if (isl_schedule_foreach_schedule_node(access->schedule,
					    &collect_sink_source, &data) < 0)
		goto error;

	flow = isl_union_flow_alloc(isl_union_map_get_space(access->sink));

	isl_compute_flow_schedule_data_align_params(&data);

	for (i = 0; i < data.n_sink; ++i)
		flow = compute_single_flow(flow, &data.sink[i], &data);

	isl_compute_flow_schedule_data_clear(&data);

	isl_union_access_info_free(access);
	return flow;
error:
	isl_union_access_info_free(access);
	isl_compute_flow_schedule_data_clear(&data);
	return NULL;
}
