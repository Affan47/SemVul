flags_set_del( int sts, void *aux )
{
	flag_vars_t *vars = (flag_vars_t *)aux;
	SVARS(vars->aux)

	if (check_ret_aux( sts, svars, t, vars ))
		return 1;
	switch (sts) {
	case DRV_OK:
		vars->srec->status |= S_DEL(t);
		Fprintf( svars->jfp, "%c %d %d 0\n", "><"[t], vars->srec->uid[M], vars->srec->uid[S] );
		vars->srec->uid[1-t] = 0;
		break;
	}
	free( vars );
	svars->flags_done[t]++;
	stats( svars );
	return msgs_flags_set( svars, t );
}
