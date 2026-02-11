waitForNetData(int limit, fd_set files)
{


    fd_set fdset = files;


    int timeout = _timeout;
    if (timeout <= 0) {
	timeout = 30;
    }
#ifdef HAVE_PSELECT_XX
    struct timespec tval;
    sigset_t pending, sigmask;
    sigprocmask(SIG_BLOCK, &sigmask, NULL);

    tval.tv_sec = 0;
    tval.tv_nsec = timeout * 1000000000;
    int ret = pselect(limit+1, &fdset, NULL, NULL, &tval, &sigmask);
    sigpending(&pending);
    if (sigismember(&pending, SIGINT)) {
	log_debug("Have a pending SIGINT interrupt waiting!");
	int sig;
	sigwait(&sigmask, &sig);
    }
    if (sigismember(&pending, SIGPIPE)) {
	log_debug("Have a pending SIGPIPE interrupt waiting!");
	int sig;
	sigwait(&sigmask, &sig);
    }
#else
    struct timeval tval;
    tval.tv_sec = 0;
    tval.tv_usec = timeout * 1000;
    int ret = select(limit+1, &fdset, NULL, NULL, &tval);
#endif

    if (ret == -1 && errno == EINTR) {
	log_error (_("Waiting for data was interrupted by a system call"));
    }

    if (ret == -1) {
	log_error (_("Waiting for data for fdset, was never available for reading"));
	FD_ZERO(&fdset);
	FD_SET(0, &fdset);
	return fdset;
    }

    if (ret == 0) {

	FD_ZERO(&fdset);
	FD_SET(0, &fdset);
	return fdset;
    }

    if (ret < 0) {
	log_error(_("select() got an error: %s."), strerror(errno));
	FD_ZERO(&fdset);
	FD_SET(0, &fdset);
    } else {
	log_network(_("select() saw activity on %d file descriptors."), ret);
    }

    return fdset;
}
