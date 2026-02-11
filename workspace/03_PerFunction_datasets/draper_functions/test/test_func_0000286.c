get_slice_value(geovol_file * vf, int x, int y, int z, void *value)
{
    slice_data *sd = (slice_data *) vf->buff;


    if ((z >= sd->crnt - (sd->base - 1)) &&
	(z <= sd->crnt + sd->num - sd->base)) {

	get_buff_value(vf->data_type, sd->slice[(z - sd->crnt)], y * Cols + x,
		       value);
    }


    else if (z == sd->crnt - (sd->base - 1) + 1) {
	shift_slices(vf);
	get_buff_value(vf->data_type, sd->slice[(z - sd->crnt)], y * Cols + x,
		       value);
    }


    else {
	return (-1);
    }

    return (1);
}
