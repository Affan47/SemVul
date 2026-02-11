gfs2_lm_withdraw(struct gfs2_sbd *sdp, const char *fmt, ...)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;
	const struct lm_lockops *lm = ls->ls_ops;
	va_list args;
	struct va_format vaf;

	if (sdp->sd_args.ar_errors == GFS2_ERRORS_WITHDRAW &&
	    test_and_set_bit(SDF_SHUTDOWN, &sdp->sd_flags))
		return 0;

	va_start(args, fmt);

	vaf.fmt = fmt;
	vaf.va = &args;

	fs_err(sdp, "%pV", &vaf);

	va_end(args);

	if (sdp->sd_args.ar_errors == GFS2_ERRORS_WITHDRAW) {
		fs_err(sdp, "about to withdraw this file system\n");
		BUG_ON(sdp->sd_args.ar_debug);

		kobject_uevent(&sdp->sd_kobj, KOBJ_OFFLINE);

		if (!strcmp(sdp->sd_lockstruct.ls_ops->lm_proto_name, "lock_dlm"))
			wait_for_completion(&sdp->sd_wdack);

		if (lm->lm_unmount) {
			fs_err(sdp, "telling LM to unmount\n");
			lm->lm_unmount(sdp);
		}
		fs_err(sdp, "withdrawn\n");
		dump_stack();
	}

	if (sdp->sd_args.ar_errors == GFS2_ERRORS_PANIC)
		panic("GFS2: fsid=%s: panic requested\n", sdp->sd_fsname);

	return -1;
}
