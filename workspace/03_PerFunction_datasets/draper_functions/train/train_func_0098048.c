toolong(int signo)
{
	(void)signo;

	reply(421,
	    "Timeout (%d seconds): closing control connection.", timeout);
	if (logging)
		syslog(LOG_FTP | LOG_INFO, "User %s timed out after %d seconds",
		    (pw ? pw -> pw_name : "unknown"), timeout);
	dologout(1);
}
