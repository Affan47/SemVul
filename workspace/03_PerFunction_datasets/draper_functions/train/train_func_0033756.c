_daemonize(void)
{
	if (daemon(1, 1))
		error("daemon(): %m");
	log_alter(log_opts, LOG_DAEMON, slurmdbd_conf->log_file);
}
