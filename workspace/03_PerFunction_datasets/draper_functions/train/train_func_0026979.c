select_setup(int *nfds, fd_set *readfds, fd_set *writefds,
    fd_set *exceptfds, struct timeval **timeout, struct timeval *timebuf)
{
	input_t *ip;
	int r = 0;

	for (ip = inputs; ip != (input_t *)NULL; ip = ip->next) {
		if ((unsigned long)ip->condition & InputReadMask) {
			FD_SET(ip->source, readfds);
			if (ip->source >= *nfds)
				*nfds = ip->source + 1;
			r = 1;
		}
		if ((unsigned long)ip->condition & InputWriteMask) {
			FD_SET(ip->source, writefds);
			if (ip->source >= *nfds)
				*nfds = ip->source + 1;
			r = 1;
		}
		if ((unsigned long)ip->condition & InputExceptMask) {
			FD_SET(ip->source, exceptfds);
			if (ip->source >= *nfds)
				*nfds = ip->source + 1;
			r = 1;
		}
	}
	if (timeouts != TN) {
		struct timeval now, twait;

		(void) gettimeofday(&now, (void *)NULL);
		twait.tv_sec = timeouts->tv.tv_sec - now.tv_sec;
		twait.tv_usec = timeouts->tv.tv_usec - now.tv_usec;
		if (twait.tv_usec < 0L) {
			twait.tv_sec--;
			twait.tv_usec += MILLION;
		}
		if (twait.tv_sec < 0L)
			twait.tv_sec = twait.tv_usec = 0L;

		if (*timeout == NULL) {

			*timebuf = twait;
			*timeout = timebuf;
			r = 1;
		} else if (twait.tv_sec < (*timeout)->tv_sec ||
		           (twait.tv_sec == (*timeout)->tv_sec &&
		            twait.tv_usec < (*timeout)->tv_usec)) {

			**timeout = twait;
			r = 1;
		}
	}
	return r;
}
