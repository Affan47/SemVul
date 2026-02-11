sigint_handler(int sig)
{
	signal(sig, SIG_DFL);
	if (verbose >= 0)
		syslog(LOG_NOTICE, "signal %d received, going down.\n", sig);
	if (child)
		kill(child, SIGHUP);
	go_down = 1;
}
