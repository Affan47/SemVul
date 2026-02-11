reopen_server_socket(dtls_listener_relay_server_type* server, evutil_socket_t fd)
{
	UNUSED_ARG(fd);

	if(!server)
		return 0;

	FUNCSTART;

	{
		EVENT_DEL(server->udp_listen_ev);

		if(server->udp_listen_s->fd>=0) {
			socket_closesocket(server->udp_listen_s->fd);
			server->udp_listen_s->fd = -1;
		}

		if (!(server->udp_listen_s)) {
			return create_server_socket(server,1);
		}

		ioa_socket_raw udp_listen_fd = socket(server->addr.ss.sa_family, SOCK_DGRAM, 0);
		if (udp_listen_fd < 0) {
			perror("socket");
			FUNCEND;
			return -1;
		}

		server->udp_listen_s->fd = udp_listen_fd;


		set_socket_options(server->udp_listen_s);

		set_sock_buf_size(udp_listen_fd, UR_SERVER_SOCK_BUF_SIZE);

		if (sock_bind_to_device(udp_listen_fd, (unsigned char*) server->ifname) < 0) {
				TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO,
				"Cannot bind listener socket to device %s\n",
				server->ifname);
		}

		if(addr_bind(udp_listen_fd,&server->addr,1)<0) {
			perror("Cannot bind local socket to addr");
			char saddr[129];
			addr_to_string(&server->addr,(u08bits*)saddr);
			TURN_LOG_FUNC(TURN_LOG_LEVEL_INFO,"Cannot bind listener socket to addr %s\n",saddr);
			return -1;
		}

		server->udp_listen_ev = event_new(server->e->event_base, udp_listen_fd,
				EV_READ | EV_PERSIST, udp_server_input_handler,
				server);

		event_add(server->udp_listen_ev, NULL );
	}

	if (!turn_params.no_udp && !turn_params.no_dtls)
		addr_debug_print(server->verbose, &server->addr,
					"UDP/DTLS listener opened on ");
	else if (!turn_params.no_dtls)
		addr_debug_print(server->verbose, &server->addr,
					"DTLS listener opened on ");
	else if (!turn_params.no_udp)
		addr_debug_print(server->verbose, &server->addr,
				"UDP listener opened on ");

	FUNCEND;

	return 0;
}
