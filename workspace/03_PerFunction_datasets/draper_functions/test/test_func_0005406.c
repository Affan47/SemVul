N_alloc_array_3d(int cols, int rows, int depths, int offset,
			     int type)
{
    N_array_3d *data = NULL;

    if (rows < 1 || cols < 1 || depths < 1)
	G_fatal_error
	    ("N_alloc_array_3d: depths, cols and rows should be > 0");

    if (type != DCELL_TYPE && type != FCELL_TYPE)
	G_fatal_error
	    ("N_alloc_array_3d: Wrong data type, should be FCELL_TYPE or DCELL_TYPE");

    data = (N_array_3d *) G_calloc(1, sizeof(N_array_3d));

    data->cols = cols;
    data->rows = rows;
    data->depths = depths;
    data->type = type;
    data->offset = offset;
    data->rows_intern = rows + 2 * offset;
    data->cols_intern = cols + 2 * offset;
    data->depths_intern = depths + 2 * offset;
    data->fcell_array = NULL;
    data->dcell_array = NULL;

    if (data->type == FCELL_TYPE) {
	data->fcell_array =
	    (float *)G_calloc(data->depths_intern * data->rows_intern *
			      data->cols_intern, sizeof(float));
	G_debug(3,
		"N_alloc_array_3d: float array allocated rows_intern %i cols_intern %i depths_intern %i offset %i",
		data->rows_intern, data->cols_intern, data->depths_intern,
		data->offset = offset);
    }
    else if (data->type == DCELL_TYPE) {
	data->dcell_array =
	    (double *)G_calloc(data->depths_intern * data->rows_intern *
			       data->cols_intern, sizeof(double));
	G_debug(3,
		"N_alloc_array_3d: double array allocated rows_intern %i cols_intern %i depths_intern %i offset %i",
		data->rows_intern, data->cols_intern, data->depths_intern,
		data->offset = offset);
    }

    return data;
}
