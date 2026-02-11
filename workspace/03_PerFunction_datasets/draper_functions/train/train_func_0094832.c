gog_series_get_data (GogSeries const *series, int *indices, double **data, int n_vectors)
{
	GOData *vector;
	int i, n_points = 0, vector_n_points;
	int first, last;
	int index;
	gboolean is_set = FALSE;

	if (!gog_series_is_valid (series))
		return 0;

	gog_dataset_dims (GOG_DATASET (series), &first, &last);

	for (i = 0; i < n_vectors; i++) {
		index = indices != NULL ? indices[i] : i;
		if (index >= first && index <= last &&
		    (vector = series->values[index].data) != NULL) {
			data[i] = go_data_get_values (vector);
			vector_n_points = go_data_get_vector_size (vector);
			if (!is_set) {
				is_set = TRUE;
				n_points = vector_n_points;
			} else
				n_points = MIN (vector_n_points, n_points);
		} else
			data[i] = NULL;
	}

	return n_points;
}
