gvl_file_start_read(geovol_file * vf)
{
    int i;
    slice_data *sd;


    if (vf->status == STATUS_BUSY)
	return (-1);

    switch (vf->mode) {

    case (MODE_FULL):

	if (0 > alloc_vol_buff(vf))
	    return (-1);


	read_vol(vf);
	break;


    case (MODE_SLICE):

	if (0 > alloc_slice_buff(vf))
	    return (-1);


	sd = (slice_data *) vf->buff;

	sd->crnt = 0;


	for (i = 0; i < (sd->num - sd->base + 1); i++)
	    read_slice(vf, (sd->base - 1) + i, i);
	break;
    }


    vf->status = STATUS_BUSY;

    return (1);
}
