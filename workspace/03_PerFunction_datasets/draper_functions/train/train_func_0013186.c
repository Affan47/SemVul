xl_surface_plot_build_matrix (GogXYZPlot *plot, gboolean *cardinality_changed)
{
	unsigned i, j, length;
	double val;
	GogSeries *series = NULL;
	GOData *vec;
	unsigned n = plot->rows * plot->columns;
	double *data;
	GSList *ptr;

	data = g_new (double, n);
	for (i = 0, ptr = plot->base.series ; ptr != NULL ; ptr = ptr->next) {
		series = ptr->data;
		if (!gog_series_is_valid (GOG_SERIES (series)))
			continue;
		vec = series->values[1].data;
		length = go_data_get_vector_size (vec);
		for (j = 0; j < plot->columns; j++) {

			val = (j < length)? go_data_get_vector_value (vec, j): 0.;

			if (val == go_nan || !go_finite (val))
				val = 0.;
			if (fabs (val) == DBL_MAX)
				val = go_nan;
			data[i * plot->columns + j] = val;
		}
		i++;
	}
	*cardinality_changed = FALSE;
	return data;
}
