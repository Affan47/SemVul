load_box( sync_vars_t *svars, int t, int minwuid, int *mexcs, int nmexcs )
{
	sync_rec_t *srec;
	int maxwuid;

	if (svars->ctx[t]->opts & OPEN_NEW) {
		if (minwuid > svars->maxuid[t] + 1)
			minwuid = svars->maxuid[t] + 1;
		maxwuid = INT_MAX;
	} else if (svars->ctx[t]->opts & OPEN_OLD) {
		maxwuid = 0;
		for (srec = svars->srecs; srec; srec = srec->next)
			if (!(srec->status & S_DEAD) && srec->uid[t] > maxwuid)
				maxwuid = srec->uid[t];
	} else
		maxwuid = 0;
	info( "Loading %s...\n", str_ms[t] );
	debug( maxwuid == INT_MAX ? "loading %s [%d,inf]\n" : "loading %s [%d,%d]\n", str_ms[t], minwuid, maxwuid );
	svars->drv[t]->load( svars->ctx[t], minwuid, maxwuid, svars->newuid[t], mexcs, nmexcs, box_loaded, AUX );
}
