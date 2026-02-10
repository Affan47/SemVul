hup(sig)
    int sig;
{
    syslog(LOG_INFO, "Hangup (SIGHUP)");
    kill_link = 1;
    if (conn_running)

	kill_my_pg(sig);
    if (waiting)
	longjmp(sigjmp, 1);
}
