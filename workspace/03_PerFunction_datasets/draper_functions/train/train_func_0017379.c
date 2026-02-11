gfs2_lm_mount(struct gfs2_sbd *sdp, int silent)
{
	const struct lm_lockops *lm;
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	struct gfs2_args *args = &sdp->sd_args;
	const char *proto = sdp->sd_proto_name;
	const char *table = sdp->sd_table_name;
	char *o, *options;
	int ret;

	if (!strcmp("lock_nolock", proto)) {
		lm = &nolock_ops;
		sdp->sd_args.ar_localflocks = 1;
#ifdef CONFIG_GFS2_FS_LOCKING_DLM
	} else if (!strcmp("lock_dlm", proto)) {
		lm = &gfs2_dlm_ops;
#endif
	} else {
		pr_info("can't find protocol %s\n", proto);
		return -ENOENT;
	}

	fs_info(sdp, "Trying to join cluster \"%s\", \"%s\"\n", proto, table);

	ls->ls_ops = lm;
	ls->ls_first = 1;

	for (options = args->ar_hostdata; (o = strsep(&options, ":")); ) {
		substring_t tmp[MAX_OPT_ARGS];
		int token, option;

		if (!o || !*o)
			continue;

		token = match_token(o, *lm->lm_tokens, tmp);
		switch (token) {
		case Opt_jid:
			ret = match_int(&tmp[0], &option);
			if (ret || option < 0)
				goto hostdata_error;
			if (test_and_clear_bit(SDF_NOJOURNALID, &sdp->sd_flags))
				ls->ls_jid = option;
			break;
		case Opt_id:
		case Opt_nodir:

			break;
		case Opt_first:
			ret = match_int(&tmp[0], &option);
			if (ret || (option != 0 && option != 1))
				goto hostdata_error;
			ls->ls_first = option;
			break;
		case Opt_err:
		default:
hostdata_error:
			fs_info(sdp, "unknown hostdata (%s)\n", o);
			return -EINVAL;
		}
	}

	if (lm->lm_mount == NULL) {
		fs_info(sdp, "Now mounting FS...\n");
		complete_all(&sdp->sd_locking_init);
		return 0;
	}
	ret = lm->lm_mount(sdp, table);
	if (ret == 0)
		fs_info(sdp, "Joined cluster. Now mounting FS...\n");
	complete_all(&sdp->sd_locking_init);
	return ret;
}
