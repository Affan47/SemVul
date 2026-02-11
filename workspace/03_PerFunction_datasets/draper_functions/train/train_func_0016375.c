dfilter_by_copy(dir_t * sp_dir_in,  dir_t * sp_dir_out, dfilter_t *sp_f)
{

	int i;
	dfilter_t * ps_f_copy;

	if ( ! sp_dir_in || ! sp_dir_out || !sp_f )
	{
		printf("One of params is wrong\n");
		return(-1);
	}

	dir_t_lock(sp_dir_in);
	dir_t_lock(sp_dir_out);

	if ( !sp_dir_out->entry || sp_dir_out->entry_allocated < sp_dir_in->amount )
	{
		dir_t_allocate_entry(sp_dir_out, sp_dir_in->amount);
	}

	sp_dir_out->amount = 0;

	for ( i = 0; i < sp_dir_in->amount ; i++ )
	{
		if ( 0 == dfilter_test_entry(sp_f, &sp_dir_in->entry[i]) )
		{

			memcpy(&(sp_dir_out->entry[sp_dir_out->amount++]), &(sp_dir_in->entry[i]), sizeof(entry_t));
		}
	}

	if ( sp_dir_out->filter != sp_f)
	{
		ps_f_copy = dfilter_copy(sp_f);
		if ( sp_dir_out->filter )
		{
			if (sp_dir_out->filter)dfilter_free(sp_dir_out->filter);
			sp_dir_out->filter = ps_f_copy;
		}
	}

	dir_t_unlock(sp_dir_out);
	dir_t_unlock(sp_dir_in);
	return(0);
}
