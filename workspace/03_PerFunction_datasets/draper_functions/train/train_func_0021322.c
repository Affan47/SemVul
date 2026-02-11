set_new_starttime(int sig)
{
	init_signals();

	starttime = time(NULL);

	if (dodebug) log(LOG_DEBUG, "new starttime is %ld.", starttime);
}
