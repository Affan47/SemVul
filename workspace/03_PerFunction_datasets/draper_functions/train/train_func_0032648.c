re_open_logfile(void)
{
	FILE           *logfp;

	if (no_log || hs == (httpd_server *) 0)
		return;


	if (logfile != (char *)0 && strcmp(logfile, "-") != 0) {
		syslog(LOG_NOTICE, "re-opening logfile");
		logfp = fopen(logfile, "a");
		if (logfp == (FILE *) 0) {
			syslog(LOG_CRIT, "re-opening %.80s - %m", logfile);
			return;
		}
		(void)fcntl(fileno(logfp), F_SETFD, 1);
		httpd_set_logfp(hs, logfp);
	}
}
