new_listener(int socks[], unsigned int nsocks,
		int type, void* typedata,
		void (*acceptor)(struct Listener* listener, int sock),
		void (*cleanup)(struct Listener*)) {

	unsigned int i, j;
	struct Listener *newlisten = NULL;

	for (i = 0; i < ses.listensize; i++) {
		if (ses.listeners[i] == NULL) {
			break;
		}
	}


	if (i == ses.listensize) {
		if (ses.listensize > MAX_LISTENERS) {
			TRACE(("leave newlistener: too many already"))
			for (j = 0; j < nsocks; j++) {
				close(socks[i]);
			}
			return NULL;
		}

		ses.listeners = (struct Listener**)m_realloc(ses.listeners,
				(ses.listensize+LISTENER_EXTEND_SIZE)
				*sizeof(struct Listener*));

		ses.listensize += LISTENER_EXTEND_SIZE;

		for (j = i; j < ses.listensize; j++) {
			ses.listeners[j] = NULL;
		}
	}

	for (j = 0; j < nsocks; j++) {
		ses.maxfd = MAX(ses.maxfd, socks[j]);
	}

	TRACE(("new listener num %d ", i))

	newlisten = (struct Listener*)m_malloc(sizeof(struct Listener));
	newlisten->index = i;
	newlisten->type = type;
	newlisten->typedata = typedata;
	newlisten->nsocks = nsocks;
	memcpy(newlisten->socks, socks, nsocks * sizeof(int));
	newlisten->acceptor = acceptor;
	newlisten->cleanup = cleanup;

	ses.listeners[i] = newlisten;
	return newlisten;
}
