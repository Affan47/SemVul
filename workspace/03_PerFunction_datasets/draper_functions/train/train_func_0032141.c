handle_alrm(int sig)
{
	const int	oerrno = errno;


	if (!watchdog_flag) {

		(void)chdir("/tmp");

		abort();
	}
	watchdog_flag = 0;

#ifndef HAVE_SIGSET

	(void)signal(SIGALRM, handle_alrm);
#endif

	(void)alarm(OCCASIONAL_TIME * 3);


	errno = oerrno;
}
