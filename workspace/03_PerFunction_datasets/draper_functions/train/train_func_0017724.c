fdevent_init(size_t maxfds, fdevent_handler_t type) {
	fdevents *ev;

	ev = calloc(1, sizeof(*ev));
	ev->fdarray = calloc(maxfds, sizeof(*ev->fdarray));
	ev->maxfds = maxfds;

	switch(type) {
	case FDEVENT_HANDLER_POLL:
		if (0 != fdevent_poll_init(ev)) {
			fprintf(stderr, "%s.%d: event-handler poll failed\n",
				__FILE__, __LINE__);

			return NULL;
		}
		break;
	case FDEVENT_HANDLER_SELECT:
		if (0 != fdevent_select_init(ev)) {
			fprintf(stderr, "%s.%d: event-handler select failed\n",
				__FILE__, __LINE__);
			return NULL;
		}
		break;
	case FDEVENT_HANDLER_LINUX_RTSIG:
		if (0 != fdevent_linux_rtsig_init(ev)) {
			fprintf(stderr, "%s.%d: event-handler linux-rtsig failed, try to set server.event-handler = \"poll\" or \"select\"\n",
				__FILE__, __LINE__);
			return NULL;
		}
		break;
	case FDEVENT_HANDLER_LINUX_SYSEPOLL:
		if (0 != fdevent_linux_sysepoll_init(ev)) {
			fprintf(stderr, "%s.%d: event-handler linux-sysepoll failed, try to set server.event-handler = \"poll\" or \"select\"\n",
				__FILE__, __LINE__);
			return NULL;
		}
		break;
	case FDEVENT_HANDLER_SOLARIS_DEVPOLL:
		if (0 != fdevent_solaris_devpoll_init(ev)) {
			fprintf(stderr, "%s.%d: event-handler solaris-devpoll failed, try to set server.event-handler = \"poll\" or \"select\"\n",
				__FILE__, __LINE__);
			return NULL;
		}
		break;
	case FDEVENT_HANDLER_FREEBSD_KQUEUE:
		if (0 != fdevent_freebsd_kqueue_init(ev)) {
			fprintf(stderr, "%s.%d: event-handler freebsd-kqueue failed, try to set server.event-handler = \"poll\" or \"select\"\n",
				__FILE__, __LINE__);
			return NULL;
		}
		break;
	default:
		fprintf(stderr, "%s.%d: event-handler is unknown, try to set server.event-handler = \"poll\" or \"select\"\n",
			__FILE__, __LINE__);
		return NULL;
	}

	return ev;
}
