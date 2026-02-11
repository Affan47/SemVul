N_convert_array_2d_null_to_zero(N_array_2d * a)
{
    int i = 0, count = 0;

    G_debug(3, "N_convert_array_2d_null_to_zero: convert array of size %i",
	    a->cols_intern * a->rows_intern);

    if (a->type == CELL_TYPE)
	for (i = 0; i < a->cols_intern * a->rows_intern; i++) {
	    if (G_is_c_null_value((void *)&(a->cell_array[i]))) {
		a->cell_array[i] = 0;
		count++;
	    }
	}

    if (a->type == FCELL_TYPE)
	for (i = 0; i < a->cols_intern * a->rows_intern; i++) {
	    if (G_is_f_null_value((void *)&(a->fcell_array[i]))) {
		a->fcell_array[i] = 0.0;
		count++;
	    }
	}


    if (a->type == DCELL_TYPE)
	for (i = 0; i < a->cols_intern * a->rows_intern; i++) {
	    if (G_is_d_null_value((void *)&(a->dcell_array[i]))) {
		a->dcell_array[i] = 0.0;
		count++;
	    }
	}


    if (a->type == CELL_TYPE)
	G_debug(2,
		"N_convert_array_2d_null_to_zero: %i values of type CELL_TYPE are converted",
		count);
    if (a->type == FCELL_TYPE)
	G_debug(2,
		"N_convert_array_2d_null_to_zero: %i valuess of type FCELL_TYPE are converted",
		count);
    if (a->type == DCELL_TYPE)
	G_debug(2,
		"N_convert_array_2d_null_to_zero: %i valuess of type DCELL_TYPE are converted",
		count);

    return count;
}
