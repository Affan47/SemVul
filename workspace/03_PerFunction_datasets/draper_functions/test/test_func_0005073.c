listener_read_cb(evutil_socket_t fd, short what, void *p)
{
	struct evconnlistener *lev = p;
	int err;
	evconnlistener_cb cb;
	evconnlistener_errorcb errorcb;
	void *user_data;
	LOCK(lev);
	while (1) {
		struct sockaddr_storage ss;
#ifdef WIN32
		int socklen = sizeof(ss);
#else
		socklen_t socklen = sizeof(ss);
#endif
		evutil_socket_t new_fd = accept(fd, (struct sockaddr*)&ss, &socklen);
		if (new_fd < 0)
			break;
		if (socklen == 0) {


			evutil_closesocket(new_fd);
			continue;
		}

		if (!(lev->flags & LEV_OPT_LEAVE_SOCKETS_BLOCKING))
			evutil_make_socket_nonblocking(new_fd);

		if (lev->cb == NULL) {
			UNLOCK(lev);
			return;
		}
		++lev->refcnt;
		cb = lev->cb;
		user_data = lev->user_data;
		UNLOCK(lev);
		cb(lev, new_fd, (struct sockaddr*)&ss, (int)socklen,
		    user_data);
		LOCK(lev);
		if (lev->refcnt == 1) {
			int freed = listener_decref_and_unlock(lev);
			EVUTIL_ASSERT(freed);
			return;
		}
		--lev->refcnt;
	}
	err = evutil_socket_geterror(fd);
	if (EVUTIL_ERR_ACCEPT_RETRIABLE(err)) {
		UNLOCK(lev);
		return;
	}
	if (lev->errorcb != NULL) {
		++lev->refcnt;
		errorcb = lev->errorcb;
		user_data = lev->user_data;
		UNLOCK(lev);
		errorcb(lev, user_data);
		LOCK(lev);
		listener_decref_and_unlock(lev);
	} else {
		event_sock_warn(fd, "Error from accept() call");
	}
}
