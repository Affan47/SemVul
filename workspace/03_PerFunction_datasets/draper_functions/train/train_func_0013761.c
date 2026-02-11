_update_logging(void)
{
	log_options_t *o = &conf->log_opts;
	slurm_ctl_conf_t *cf;


	cf = slurm_conf_lock();
	if ( (conf->debug_level == LOG_LEVEL_INFO)
	     && (cf->slurmd_debug != (uint16_t) NO_VAL) )
		conf->debug_level = cf->slurmd_debug;
	slurm_conf_unlock();

	o->stderr_level  = conf->debug_level;
	o->logfile_level = conf->debug_level;
	o->syslog_level  = conf->debug_level;


	if (conf->daemonize) {
		o->stderr_level = LOG_LEVEL_QUIET;
		if (conf->logfile)
			o->syslog_level = LOG_LEVEL_FATAL;
	} else
		o->syslog_level  = LOG_LEVEL_QUIET;

	log_alter(conf->log_opts, SYSLOG_FACILITY_DAEMON, conf->logfile);
}
