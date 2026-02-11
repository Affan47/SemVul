ADIOI_init_view_state(int file_ptr_type,
		    int nprocs,
		    view_state *view_state_arr,
		    int op_type)
{
    ADIOI_Flatlist_node *tmp_flat_type_p = NULL;
    ADIO_Offset tmp_off_used = 0, st_reg = 0, tmp_reg_sz = 0;
    int i;
    flatten_state *tmp_state_p = NULL;
    view_state *tmp_view_p = NULL;

    for (i = 0; i < nprocs; i++)
    {
	switch(op_type)
	{
	    case TEMP_OFF:
		tmp_state_p = &(view_state_arr[i].tmp_state);
		break;
	    case REAL_OFF:
		tmp_state_p = &(view_state_arr[i].cur_state);
		break;
	    default:
		fprintf(stderr, "op_type invalid\n");
	}

	tmp_view_p = &(view_state_arr[i]);
	tmp_flat_type_p = tmp_view_p->flat_type_p;

	if (file_ptr_type == ADIO_INDIVIDUAL)
	    tmp_state_p->abs_off = tmp_view_p->fp_ind;
	else
	    tmp_state_p->abs_off = tmp_view_p->disp;

	tmp_off_used = 0;


	while (tmp_flat_type_p->blocklens[tmp_state_p->idx] == 0)
	    tmp_state_p->idx = (tmp_state_p->idx + 1) % tmp_flat_type_p->count;
	if (file_ptr_type == ADIO_EXPLICIT_OFFSET)
	    tmp_state_p->abs_off += tmp_flat_type_p->indices[tmp_state_p->idx];


	while (tmp_off_used != tmp_view_p->byte_off)
	{
	    view_state_add_region(
		tmp_view_p->byte_off - tmp_off_used,
		&(view_state_arr[i]), &st_reg, &tmp_reg_sz,
		op_type);
	}


	tmp_state_p->cur_sz = 0;
#ifdef DEBUG1
	fprintf(stderr, "init_view_state: %s (idx=%d,byte_off=%Ld,"
		"abs_off=%Ld,reg_off=%Ld,sz=%Ld)\n", off_type_name[op_type],
		i, tmp_view_p->byte_off, tmp_state_p->abs_off,
		tmp_state_p->cur_reg_off, tmp_view_p->sz);
#endif

    }
    return 0;
}
