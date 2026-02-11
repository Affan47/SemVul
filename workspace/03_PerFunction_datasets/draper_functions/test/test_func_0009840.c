select_resize(struct selectop *sop, int fdsz)
{
	fd_set *readset_in = NULL;
	fd_set *writeset_in = NULL;

	if (sop->event_readset_in)
		check_selectop(sop);

	if ((readset_in = mm_realloc(sop->event_readset_in, fdsz)) == NULL)
		goto error;
	sop->event_readset_in = readset_in;
	if ((writeset_in = mm_realloc(sop->event_writeset_in, fdsz)) == NULL) {


		goto error;
	}
	sop->event_writeset_in = writeset_in;
	sop->resize_out_sets = 1;

	memset((char *)sop->event_readset_in + sop->event_fdsz, 0,
	    fdsz - sop->event_fdsz);
	memset((char *)sop->event_writeset_in + sop->event_fdsz, 0,
	    fdsz - sop->event_fdsz);

	sop->event_fdsz = fdsz;
	check_selectop(sop);

	return (0);

 error:
	event_warn("malloc");
	return (-1);
}
