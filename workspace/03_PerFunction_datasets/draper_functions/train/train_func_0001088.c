sync_idle_dosync_collectedevents_rsync_exclistpush(gpointer fpath_gp, gpointer flags_gp, gpointer arg_gp) {
	struct dosync_arg *dosync_arg_p = (struct dosync_arg *)arg_gp;
	char *fpath		  = (char *)fpath_gp;
	FILE *excf		  = dosync_arg_p->outf;
	eventinfo_flags_t flags	  = GPOINTER_TO_INT(flags_gp);


	printf_ddd("Debug3: sync_idle_dosync_collectedevents_rsync_exclistpush(): \"%s\"\n", fpath);

	size_t fpath_len = strlen(fpath);
	char *fpathwslash;
	if(fpath_len>0) {


		fpathwslash = alloca(fpath_len+2);
		fpathwslash[0] = '/';
		memcpy(&fpathwslash[1], fpath, fpath_len+1);
	} else {


		fpathwslash = fpath;
	}

	fpathwslash = (char *)rsync_escape(fpathwslash);

	int ret;
	if((ret=rsync_outline(excf, fpathwslash, flags))) {
		printf_e("Error: sync_idle_dosync_collectedevents_rsync_exclistpush(): Got error from rsync_outline(). Exit.\n");
		exit(ret);
	}

	return TRUE;
}
