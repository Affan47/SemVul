update_async(void)
{
    int time = tl_process_group(asyncgroup, NULL);
    if (time != -1) {
	struct itimerval t;
	t.it_interval.tv_sec = 0;
	t.it_interval.tv_usec = 0;
	t.it_value.tv_sec = time / 1000000;
	t.it_value.tv_usec = time % 1000000;
	if (!reghandler) {
	    signal(SIGALRM, alarmhandler), reghandler = 1;
	}
	setitimer(ITIMER_REAL, &t, &t);
	registered = 1;
    } else if (registered) {
	struct itimerval t;
	t.it_interval.tv_sec = 0;
	t.it_interval.tv_usec = 0;
	t.it_value.tv_sec = 0;
	t.it_value.tv_usec = 0;
	setitimer(ITIMER_REAL, &t, &t);
	registered = 0;
    }
}
