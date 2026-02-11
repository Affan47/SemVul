ekg_connect_loop(struct ekg_connect_data *c) {
	char *host;
	session_t *s = session_find(c->session);

	if (!s) {
		debug_error("ekg_connect_loop(), looks like session '%s' vanished!\n", c->session);
		ekg_connect_data_free(c);
		return 0;
	}


	if ((host = array_shift(&(c->connect_queue))) || (host = array_shift(&(c->connect_queue2)))) {
		struct sockaddr *addr;
		int len, fd, family, connret;
		watch_t *w;

		const int timeout = session_int_get(s, "connect_timeout");

		do {
			int one = 1;

			len = ekg_build_sin(host, c->port, &addr, &family);
			debug_function("ekg_connect_loop(), connect: %s, sinlen: %d\n", host, len);
			xfree(host);
			if (!len)
				break;

			if ((fd = socket(family, SOCK_STREAM, 0)) == -1) {
				const int err = errno;
				debug_error("ekg_connect_loop(), socket() failed: %s\n", strerror(err));
				break;
			}
			setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &one, sizeof(one));
			if (ioctl(fd, FIONBIO, &one) == -1) {
				const int err = errno;
				debug_error("ekg_connect_loop(), ioctl() failed: %s\n", strerror(err));
				close(fd);
				break;
			}

			connret = connect(fd, addr, len);
			if (connret && errno != EINPROGRESS) {
				const int err = errno;
				debug_error("ekg_connect_loop(), connect() failed: %s\n", strerror(err));
				close(fd);
				break;
			}

			w = watch_add(s->plugin, fd, WATCH_WRITE, ekg_connect_handler, c);

			if (timeout > 0)
				watch_timeout_set(w, timeout);

			xfree(addr);
			c->current_watch = w;
			return 1;
		} while (0);

		xfree(addr);
	}


	if ((host = array_shift(&(c->resolver_queue)))) {
		watch_t *w;

		debug_function("ekg_connect_loop(), resolve: %s\n", host);
		w = ekg_resolver4(s->plugin, host, (void*) ekg_connect_resolver_handler, c, c->proto_port, c->port, IPPROTO_TCP);
		xfree(host);

		c->current_watch = w;
		return 1;
	}


	if (s)
		c->async(-1, -1, WATCH_WRITE, s);
	ekg_connect_data_free(c);
	return 0;
}
