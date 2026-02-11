accept_tcp_cb(EV_P_ ev_io *w, int revents __attribute__((__unused__)))
{
	tls_server_state *ctx = w->data;

	while (1) {
		tls_state *tls;

		if (BIO_do_accept(ctx->bio) <= 0) {
			if (BIO_should_retry(ctx->bio))
				debug("Cannot accept connection right now");
			else
				log_tls_message(warning,
				    "Cannot accept connection");
			return;
		}

		tls = tls_new(TLS_SERVER, TLS_NO_AUTO_DIE);
		tls->bio = BIO_pop(ctx->bio);
		tls->fd = (int)BIO_get_fd(tls->bio, NULL);
		tls->addr = xmalloc(INET6_ADDRSTRLEN);
		tls->connect_handler = ctx->connect_handler;
		tls->timeout = ctx->timeout;
		tls->data = ctx->data;

		if (!get_peer_address(tls->fd, tls->addr, INET6_ADDRSTRLEN)) {
			tls_free(tls);
			return;
		}

		tls_on_timeout(tls, default_timeout_handler);

		if ((tls->ssl = SSL_new(ctx->ssl)) == NULL) {
			log_tls_message(error,
			    "Cannot create SSL object for %s", tls->addr);
			tls_free(tls);
			return;
		}
		SSL_set_bio(tls->ssl, tls->bio, tls->bio);

		ev_io_set(&tls->init_watcher, tls->fd, EV_READ);
		ev_io_start(EV_A_ &tls->init_watcher);
		ev_feed_event(EV_A_ &tls->init_watcher, EV_READ);

		debug("Accepted connection from %s", tls->addr);
	}
}
