_slurmd_job_log_init(slurmd_job_t *job)
{
	char argv0[64];

	conf->log_opts.buffered = 1;


	conf->log_opts.stderr_level = LOG_LEVEL_ERROR + job->debug;
	if (conf->log_opts.stderr_level > LOG_LEVEL_DEBUG3)
		conf->log_opts.stderr_level = LOG_LEVEL_DEBUG3;

	snprintf(argv0, sizeof(argv0), "slurmd[%s]", conf->node_name);


	log_alter(conf->log_opts, 0, NULL);
	log_set_argv0(argv0);


	if (!job->user_managed_io && !job->pty && job->task != NULL) {
		if (dup2(job->task[0]->stderr_fd, STDERR_FILENO) < 0) {
			error("job_log_init: dup2(stderr): %m");
			return ESLURMD_IO_ERROR;
		}
	}
	verbose("debug level = %d", conf->log_opts.stderr_level);
	return SLURM_SUCCESS;
}
