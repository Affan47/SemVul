interruptible_idle(int seconds)

{
    int awoken = FALSE;

#ifndef __EMX__
#ifdef SLEEP_WITH_ALARM


    {
    struct itimerval ntimeout;

    ntimeout.it_interval.tv_sec = 5;
    ntimeout.it_interval.tv_usec = 0;
    ntimeout.it_value.tv_sec  = seconds;
    ntimeout.it_value.tv_usec = 0;

    alarm_latch = FALSE;
    set_signal_handler(SIGALRM, gotsigalrm);
    setitimer(ITIMER_REAL,&ntimeout,NULL);


    if (!alarm_latch)
	pause();

    ntimeout.it_interval.tv_sec = ntimeout.it_interval.tv_usec = 0;
    ntimeout.it_value.tv_sec  = ntimeout.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL,&ntimeout,NULL);
    set_signal_handler(SIGALRM, SIG_IGN);
    }
#else


    {
    struct timeval timeout;

    timeout.tv_sec = seconds;
    timeout.tv_usec = 0;
    do {
	lastsig = 0;
	select(0,0,0,0, &timeout);
    } while (lastsig == SIGCHLD);
    }
#endif
#else
    alarm_latch = FALSE;
    set_signal_handler(SIGALRM, gotsigalrm);
    _beginthread(itimerthread, NULL, 32768, NULL);

    if (!alarm_latch)
	pause();
    set_signal_handler(SIGALRM, SIG_IGN);
#endif
    if (lastsig == SIGUSR1 || ((seconds && getuid() == ROOT_UID)
	&& lastsig == SIGHUP))
       awoken = TRUE;


    set_signal_handler(SIGUSR1, SIG_IGN);
    if (getuid() == ROOT_UID)
	set_signal_handler(SIGHUP, SIG_IGN);

    return(awoken ? lastsig : 0);
}
