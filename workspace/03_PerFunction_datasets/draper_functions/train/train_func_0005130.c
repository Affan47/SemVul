Job_CatchOutput(int flag)
#endif
{
	int		nfds;
#ifdef USE_KQUEUE
#define KEV_SIZE	4
	struct kevent	kev[KEV_SIZE];
	int		i;
#else
	struct timeval	timeout;
	fd_set		readfds;
	Job		*job;
#endif

	fflush(stdout);

	if (usePipes) {
#ifdef USE_KQUEUE
		if ((nfds = kevent(kqfd, NULL, 0, kev, KEV_SIZE, NULL)) == -1) {
			if (errno != EINTR)
				Punt("kevent: %s", strerror(errno));
			if (interrupted)
				JobPassSig(interrupted);
		} else {
			for (i = 0; i < nfds; i++) {
				if (kev[i].flags & EV_ERROR) {
					warnc(kev[i].data, "kevent");
					continue;
				}
				switch (kev[i].filter) {
				  case EVFILT_READ:
					JobDoOutput(kev[i].udata, FALSE);
					break;
				  case EVFILT_PROC:


					break;
				}
			}
		}
#else
		readfds = outputs;
		timeout.tv_sec = SEL_SEC;
		timeout.tv_usec = SEL_USEC;
		if (flag && jobFull && fifoFd >= 0)
			FD_SET(fifoFd, &readfds);

		nfds = select(FD_SETSIZE, &readfds, (fd_set *)NULL,
		    (fd_set *)NULL, &timeout);
		if (nfds <= 0) {
			if (interrupted)
				JobPassSig(interrupted);
			return;
		}
		if (fifoFd >= 0 && FD_ISSET(fifoFd, &readfds)) {
			if (--nfds <= 0)
				return;
		}
		job = TAILQ_FIRST(&jobs);
		while (nfds != 0 && job != NULL) {
			if (FD_ISSET(job->inPipe, &readfds)) {
				JobDoOutput(job, FALSE);
				nfds--;
			}
			job = TAILQ_NEXT(job, link);
		}
#endif
	}
}
