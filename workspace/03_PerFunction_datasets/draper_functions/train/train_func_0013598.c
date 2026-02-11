gog_pie_series_update (GogObject *obj)
{
	double *vals = NULL, total;
	int len = 0;
	GogPieSeries *series = GOG_PIE_SERIES (obj);
	unsigned old_num = series->base.num_elements;
	GogShowNegsMode mode = GOG_PIE_PLOT (series->base.plot)->show_negatives;

	if (series->base.values[1].data != NULL) {
		vals = go_data_get_values (series->base.values[1].data);
		len = go_data_get_vector_size (series->base.values[1].data);
	}
	series->base.num_elements = len;

	for (total = 0. ; len-- > 0 ;) {
		double val = vals[len];
		if (go_finite (val)) {
			if (val < 0)
				val = (mode == GOG_SHOW_NEGS_SKIP)? 0.: -val;
			total += val;
		}
	}
	series->total = total;


	gog_object_request_update (GOG_OBJECT (series->base.plot));
	if (old_num != series->base.num_elements)
		gog_plot_request_cardinality_update (series->base.plot);

	if (series_parent_klass->update)
		series_parent_klass->update (obj);
}
