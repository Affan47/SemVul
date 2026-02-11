sync_internal(GFS_File gf, int operation, double *time)
{
	gfarm_error_t e;
	gfarm_timerval_t t1, t2;

	GFARM_TIMEVAL_FIX_INITIALIZE_WARNING(t1);
	gfs_profile(gfarm_gettimerval(&t1));

	e = gfs_pio_flush(gf);
	if (e != GFARM_ERR_NO_ERROR) {
		gflog_debug(GFARM_MSG_1001318,
			"gfs_pio_flush() failed: %s",
			gfarm_error_string(e));
		goto finish;
	}

	e = (*gf->ops->view_fsync)(gf, operation);
	if (e != GFARM_ERR_NO_ERROR) {
		gf->error = e;
		gflog_debug(GFARM_MSG_1001319,
			"view_fsync() failed: %s",
			gfarm_error_string(e));
	}
finish:
	gfs_profile(gfarm_gettimerval(&t2));
	gfs_profile(*time += gfarm_timerval_sub(&t2, &t1));

	return (e);
}
