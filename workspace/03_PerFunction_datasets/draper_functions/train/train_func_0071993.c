tcp_listener_input_handler(struct evconnlistener *l, evutil_socket_t fd,
				struct sockaddr *sa, int socklen, void *arg)
{
	UNUSED_ARG(l);

	ioa_socket_handle list_s = (ioa_socket_handle) arg;

	ioa_addr client_addr;
	ns_bcopy(sa,&client_addr,socklen);

	addr_debug_print(((list_s->e) && list_s->e->verbose), &client_addr,"tcp accepted from");

	ioa_socket_handle s =
				create_ioa_socket_from_fd(
							list_s->e,
							fd,
							NULL,
							TCP_SOCKET,
							TCP_RELAY_DATA_SOCKET,
							&client_addr,
							&(list_s->local_addr));

	if (s) {
		if(list_s->acb) {
			list_s->acb(s,list_s->acbarg);
		} else {
			TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR,
					"Do not know what to do with accepted TCP socket\n");
			close_ioa_socket(s);
		}
	} else {
		TURN_LOG_FUNC(TURN_LOG_LEVEL_ERROR,
				"Cannot create ioa_socket from FD\n");
		socket_closesocket(fd);
	}
}
