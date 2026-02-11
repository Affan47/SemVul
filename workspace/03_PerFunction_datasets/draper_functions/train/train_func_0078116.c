evsig_handler(int sig)
{
	int save_errno = errno;
#ifdef WIN32
	int socket_errno = EVUTIL_SOCKET_ERROR();
#endif
	ev_uint8_t msg;

	if (evsig_base == NULL) {
		event_warnx(
			"%s: received signal %d, but have no base configured",
			__func__, sig);
		return;
	}

#ifndef _EVENT_HAVE_SIGACTION
	signal(sig, evsig_handler);
#endif


	msg = sig;
	send(evsig_base_fd, (char*)&msg, 1, 0);
	errno = save_errno;
#ifdef WIN32
	EVUTIL_SET_SOCKET_ERROR(socket_errno);
#endif
}
