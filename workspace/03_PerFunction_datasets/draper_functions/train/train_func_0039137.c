_handle_reconfig(int fd, stepd_step_rec_t *job, uid_t uid)
{
	int rc = SLURM_SUCCESS;
	int errnum = 0;

	if (!_slurm_authorized_user(uid)) {
		debug("job step reconfigure request from uid %ld "
		      "for job %u.%u ",
		      (long)uid, job->jobid, job->stepid);
		rc = -1;
		errnum = EPERM;
		goto done;
	}


	log_alter(conf->log_opts, SYSLOG_FACILITY_DAEMON, conf->logfile);
	debug("_handle_reconfigure for job %u.%u successful",
	      job->jobid, job->stepid);

done:

	safe_write(fd, &rc, sizeof(int));
	safe_write(fd, &errnum, sizeof(int));
	return SLURM_SUCCESS;
rwfail:
	return SLURM_FAILURE;
}
