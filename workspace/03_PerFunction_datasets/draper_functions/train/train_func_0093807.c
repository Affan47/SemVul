go_data_get_matrix_size (GOData *data, unsigned int *n_rows, unsigned int *n_columns)
{
	unsigned int sizes[2];

	if (!GO_IS_DATA (data)) {
		if (n_columns != NULL)
			*n_columns = 0;

		if (n_rows != NULL)
			*n_rows = 0;

		g_return_if_fail (GO_IS_DATA (data));
	}

	go_data_get_sizes (data, 2, sizes);

	if (n_columns != NULL)
		*n_columns = sizes[0];

	if (n_rows != NULL)
		*n_rows = sizes[1];
}
