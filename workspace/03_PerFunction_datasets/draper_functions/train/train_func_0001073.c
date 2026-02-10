_sync_idle_dosync_collectedexcludes(gpointer fpath_gp, gpointer flags_gp, gpointer arg_gp) {
	char *fpath		  = (char *)fpath_gp;
	indexes_t *indexes_p 	  = ((struct dosync_arg *)arg_gp)->indexes_p;

	printf_ddd("Debug3: _sync_idle_dosync_collectedexcludes(): \"%s\", %u (%p).\n", fpath, GPOINTER_TO_INT(flags_gp), flags_gp);

	indexes_addexclude_aggr(indexes_p, strdup(fpath), (eventinfo_flags_t)GPOINTER_TO_INT(flags_gp));

	return;
}
