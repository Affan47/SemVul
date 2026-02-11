init_scs(void)
{
	int i;

	if (scs_initted)
		return;

	trace_ds("Initializing SCS virtual 3287.\n");
	init_scs_horiz();
	init_scs_vert();
	pp = 1;
	line = 1;
	scs_any = 0;
	for (i = 0; i < MAX_MPP+1; i++)
	    	linebuf[i] = ' ';
	for (i = 0; i < MAX_MPP+1; i++) {
		if (trnbuf[i].malloc_len != 0) {
			Free(trnbuf[i].buf);
			trnbuf[i].buf = NULL;
			trnbuf[i].malloc_len = 0;
		}
		trnbuf[i].data_len = 0;
	}
	scs_leftover_len = 0;
	scs_dbcs_subfield = 0;
#if defined(X3270_DBCS)
	scs_dbcs_c1 = 0;
#endif
	scs_cs = 0;

	scs_initted = True;
}
