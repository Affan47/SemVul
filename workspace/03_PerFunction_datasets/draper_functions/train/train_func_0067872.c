get_y_vector (GogPlot *plot)
{
	GSList *ptr;
	int i;
	char const ***y_labels = (GOG_IS_CONTOUR_PLOT (plot))?
				&(XL_CONTOUR_PLOT (plot)->y_labels):
				&(XL_SURFACE_PLOT (plot)->y_labels);

	g_free (*y_labels);
	*y_labels = g_new0 (char const *, GOG_XYZ_PLOT (plot)->rows);

	for (ptr = plot->series, i = 0 ; ptr != NULL ; ptr = ptr->next, i++) {
		XLXYZSeries *series = ptr->data;

		if (!gog_series_is_valid (GOG_SERIES (series)))
			continue;
		(*y_labels) [i] = (series->values[-1].data)?
				go_data_get_scalar_string (series->values[-1].data):
				g_strdup_printf("S%d", i + 1);
	}

	return GO_DATA (go_data_vector_str_new (*y_labels, i, g_free));
}
