update_logging(void)
{
	int rc;
	uid_t slurm_user_id  = slurmctld_conf.slurm_user_id;
	gid_t slurm_user_gid = gid_from_uid(slurm_user_id);


	if (debug_level) {
		slurmctld_conf.slurmctld_debug = MIN(
			(LOG_LEVEL_INFO + debug_level),
			(LOG_LEVEL_END - 1));
	}
	if (slurmctld_conf.slurmctld_debug != (uint16_t) NO_VAL) {
		log_opts.stderr_level  = slurmctld_conf.slurmctld_debug;
		log_opts.logfile_level = slurmctld_conf.slurmctld_debug;
		log_opts.syslog_level  = slurmctld_conf.slurmctld_debug;
	}
	if (debug_logfile) {
		xfree(slurmctld_conf.slurmctld_logfile);
		slurmctld_conf.slurmctld_logfile = xstrdup(debug_logfile);
	}

	if (daemonize) {
		log_opts.stderr_level = LOG_LEVEL_QUIET;
		if (slurmctld_conf.slurmctld_logfile)
			log_opts.syslog_level = LOG_LEVEL_FATAL;
	} else
		log_opts.syslog_level = LOG_LEVEL_QUIET;

	log_alter(log_opts, SYSLOG_FACILITY_DAEMON,
		  slurmctld_conf.slurmctld_logfile);

	log_set_timefmt(slurmctld_conf.log_fmt);


	if (slurmctld_conf.sched_log_level != (uint16_t) NO_VAL)
		sched_log_opts.logfile_level = slurmctld_conf.sched_log_level;

	sched_log_alter(sched_log_opts, LOG_DAEMON,
			slurmctld_conf.sched_logfile);

	if (slurmctld_conf.slurmctld_logfile) {
		rc = chown(slurmctld_conf.slurmctld_logfile,
			   slurm_user_id, slurm_user_gid);
		if (rc && daemonize) {
			error("chown(%s, %d, %d): %m",
			      slurmctld_conf.slurmctld_logfile,
			      (int) slurm_user_id, (int) slurm_user_gid);
		}
	}
	if (slurmctld_conf.sched_logfile) {
		rc = chown(slurmctld_conf.sched_logfile,
			   slurm_user_id, slurm_user_gid);
		if (rc && daemonize) {
			error("chown(%s, %d, %d): %m",
			      slurmctld_conf.sched_logfile,
			      (int) slurm_user_id, (int) slurm_user_gid);
		}
	}
}
