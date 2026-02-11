handle_chld(int sig)
{
	const int	oerrno = errno;
	pid_t		pid;
	int		status;

#ifndef HAVE_SIGSET

	(void)signal(SIGCHLD, handle_chld);
#endif


	for (;;) {
#ifdef HAVE_WAITPID
		pid = waitpid((pid_t) - 1, &status, WNOHANG);
#else
		pid = wait3(&status, WNOHANG, (struct rusage *)0);
#endif
		if ((int)pid == 0)
			break;
		if ((int)pid < 0) {
			if (errno == EINTR || errno == EAGAIN)
				continue;


			if (errno != ECHILD)
				syslog(LOG_ERR, "child wait - %m");
			break;
		}


		if (hs != (httpd_server *) 0) {
			--hs->cgi_count;
			if (hs->cgi_count < 0)
				hs->cgi_count = 0;
		}
	}


	errno = oerrno;
}
