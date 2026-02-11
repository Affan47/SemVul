exp_disconnect()
{
	int ttyfd;

#ifndef EALREADY
#define EALREADY 37
#endif


	if (exp_disconnected) sysreturn(EALREADY);
	exp_disconnected = TRUE;

	freopen("/dev/null","r",stdin);
	freopen("/dev/null","w",stdout);
	freopen("/dev/null","w",stderr);

#ifdef POSIX
	setsid();
#else
#ifdef SYSV3

	exp_setpgrp();
	signal(SIGHUP,SIG_IGN);
	if (fork()) exit(0);


#else
	exp_setpgrp();

#ifdef TIOCNOTTY
	ttyfd = open("/dev/tty", O_RDWR);
	if (ttyfd >= 0) {

		(void) ioctl(ttyfd, TIOCNOTTY, (char *)0);
		(void) close(ttyfd);
	}
#endif
#endif
#endif
	return(0);
}
