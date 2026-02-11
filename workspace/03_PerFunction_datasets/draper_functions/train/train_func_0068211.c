gog_series1_5d_update (GogObject *obj)
{
	double *vals;
	int len = 0;
	GogSeries *series = GOG_SERIES (obj);
	unsigned old_num = series->num_elements;

	if (series->values[1].data != NULL) {
		vals = go_data_get_values (series->values[1].data);
		len = go_data_get_vector_size (series->values[1].data);
	}
	series->num_elements = len;

	if (series->plot->desc.series.num_dim == 3) {
		int tmp = 0;
		if (series->values[2].data != NULL) {
			vals = go_data_get_values (series->values[2].data);
			tmp = go_data_get_vector_size (series->values[2].data);
		}
		if (tmp < len)
			len = tmp;
	}


	gog_object_request_update (GOG_OBJECT (series->plot));
	if (old_num != series->num_elements)
		gog_plot_request_cardinality_update (series->plot);

	if (gog_series1_5d_parent_klass->update)
		gog_series1_5d_parent_klass->update (obj);
}
