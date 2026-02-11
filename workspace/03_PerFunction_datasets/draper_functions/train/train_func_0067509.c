N_get_array_2d_d_value(N_array_2d * data, int col, int row)
{
    CELL value = 0;
    FCELL fvalue = 0.0;
    DCELL dvalue = 0.0;

    switch (data->type) {
    case CELL_TYPE:
	N_get_array_2d_value(data, col, row, (void *)&value);
	return (DCELL) value;
    case FCELL_TYPE:
	N_get_array_2d_value(data, col, row, (void *)&fvalue);
	return (DCELL) fvalue;
    case DCELL_TYPE:
	N_get_array_2d_value(data, col, row, (void *)&dvalue);
	return (DCELL) dvalue;
    }

    return dvalue;

}
