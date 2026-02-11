handle_signal_self(int flag)
{
	if ((flag & (RADIUS_SIGNAL_SELF_EXIT | RADIUS_SIGNAL_SELF_TERM)) != 0) {
		if ((flag & RADIUS_SIGNAL_SELF_EXIT) != 0) {
			radlog(L_INFO, "Signalled to exit");
			fr_event_loop_exit(el, 1);
		} else {
			radlog(L_INFO, "Signalled to terminate");
			exec_trigger(NULL, NULL, "server.signal.term");
			fr_event_loop_exit(el, 2);
		}

		return;
	}


	if ((flag & RADIUS_SIGNAL_SELF_HUP) != 0) {
		time_t when;
		static time_t last_hup = 0;

		when = time(NULL);
		if ((int) (when - last_hup) < 5) {
			radlog(L_INFO, "Ignoring HUP (less than 5s since last one)");
			return;
		}

		radlog(L_INFO, "Received HUP signal.");

		last_hup = when;

		exec_trigger(NULL, NULL, "server.signal.hup");
		fr_event_loop_exit(el, 0x80);
	}

#ifdef WITH_DETAIL
	if ((flag & RADIUS_SIGNAL_SELF_DETAIL) != 0) {
		rad_listen_t *this;


		for (this = mainconfig.listen;
		     this != NULL;
		     this = this->next) {
			if (this->type != RAD_LISTEN_DETAIL) continue;


			if (!this->decode(this, NULL)) continue;


			event_poll_detail(this);
		}
	}
#endif

#ifdef WITH_TCP
#ifdef WITH_PROXY
#ifdef HAVE_PTHREAD_H


	if ((flag & RADIUS_SIGNAL_SELF_NEW_FD) != 0) {
		struct timeval when, now;

		fr_event_now(el, &now);

		PTHREAD_MUTEX_LOCK(&proxy_mutex);

		while (proxy_listener_list) {
			rad_listen_t *this = proxy_listener_list;
			listen_socket_t *sock = this->data;

			rad_assert(sock->proto == IPPROTO_TCP);
			proxy_listener_list = this->next;
			this->next = NULL;

			if (!sock->home) continue;

			when = now;

			if (!fr_event_insert(el, tcp_socket_timer, this, &when,
					     &(sock->ev))) {
				rad_panic("Failed to insert event");
			}
		}

		PTHREAD_MUTEX_UNLOCK(&proxy_mutex);
	}
#endif
#endif
#endif
}
