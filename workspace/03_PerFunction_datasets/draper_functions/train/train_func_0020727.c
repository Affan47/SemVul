N_put_array_3d_value_null(N_array_3d * data, int col, int row, int depth)
{

    G_debug(6,
	    "N_put_array_3d_value_null: put null value to array at pos [%i][%i][%i]",
	    depth, row, col);

    if (data->offset == 0) {
	if (data->type == FCELL_TYPE && data->fcell_array != NULL) {
	    G3d_setNullValue((void *)
			     &(data->
			       fcell_array[depth *
					   (data->rows_intern *
					    data->cols_intern) +
					   row * data->cols_intern + col]), 1,
			     FCELL_TYPE);
	}
	else if (data->type == DCELL_TYPE && data->dcell_array != NULL) {
	    G3d_setNullValue((void *)
			     &(data->
			       dcell_array[depth *
					   (data->rows_intern *
					    data->cols_intern) +
					   row * data->cols_intern + col]), 1,
			     DCELL_TYPE);
	}
    }
    else {
	if (data->type == FCELL_TYPE && data->fcell_array != NULL) {
	    G3d_setNullValue((void *)
			     &(data->
			       fcell_array[(depth +
					    data->offset) *
					   (data->rows_intern *
					    data->cols_intern) + (row +
								  data->
								  offset) *
					   data->cols_intern + (col +
								data->
								offset)]), 1,
			     FCELL_TYPE);
	}
	else if (data->type == DCELL_TYPE && data->dcell_array != NULL) {
	    G3d_setNullValue((void *)
			     &(data->
			       dcell_array[(depth +
					    data->offset) *
					   (data->rows_intern *
					    data->cols_intern) + (row +
								  data->
								  offset) *
					   data->cols_intern + (col +
								data->
								offset)]), 1,
			     DCELL_TYPE);
	}
    }

    return;
}
