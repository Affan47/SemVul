close_socket_net_data(ioa_socket_handle s)
{
	if(s) {

		EVENT_DEL(s->read_event);
		if(s->list_ev) {
			evconnlistener_free(s->list_ev);
			s->list_ev = NULL;
		}
		BUFFEREVENT_FREE(s->conn_bev);
		BUFFEREVENT_FREE(s->bev);

		if (s->ssl) {
			if (!s->broken) {
				if(!(SSL_get_shutdown(s->ssl) & SSL_SENT_SHUTDOWN)) {


					SSL_set_shutdown(s->ssl, SSL_RECEIVED_SHUTDOWN);
					SSL_shutdown(s->ssl);
					log_socket_event(s, "SSL shutdown received, socket to be closed",0);
				}
			}
			SSL_FREE(s->ssl);
		}

		if (s->fd >= 0) {
			socket_closesocket(s->fd);
			s->fd = -1;
		}
	}
}
