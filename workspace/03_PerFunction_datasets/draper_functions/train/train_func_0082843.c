child_death_dispatch(int sig, gpointer notused)
{
	int 			status;
	pid_t			pid;
	const int		waitflags = WNOHANG;
	struct sigaction	saveaction;
	int			childcount = 0;


	memset(&saveaction, 0, sizeof(saveaction));
	cl_signal_set_simple_handler(SIGALRM, G_main_alarm_helper, &saveaction);

	alarm_count = 0;
	cl_signal_set_interrupt(SIGALRM, TRUE);
	setmsrepeattimer(WAITALARM);
	while((pid=wait3(&status, waitflags, NULL)) > 0
	||	(pid < 0 && errno == EINTR)) {
		cancelmstimer();
		if (pid > 0) {
			++childcount;
			ReportProcHasDied(pid, status);
		}
		setmsrepeattimer(WAITALARM);
	}
	cancelmstimer();
	cl_signal_set_simple_handler(SIGALRM, saveaction.sa_handler, &saveaction);

	if (pid < 0 && errno != ECHILD) {
		cl_perror("%s: wait3() failed"
		,	__FUNCTION__);
	}
#if defined(DEBUG)
	if (childcount < 1) {


		cl_log(LOG_DEBUG, "NOTE: %s called without children to wait on"
		,	__FUNCTION__);
	}
#endif
	if (alarm_count) {
		cl_log(LOG_ERR
		,	"%s: wait3() call hung %d times. childcount = %d"
		,	__FUNCTION__, alarm_count, childcount);
		alarm_count = 0;
	}
	return TRUE;
}
