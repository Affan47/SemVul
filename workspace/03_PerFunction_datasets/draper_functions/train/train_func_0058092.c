auth_socket_recv(rad_listen_t *listener)
{
	ssize_t		rcode;
	int		code, src_port;
	RADIUS_PACKET	*packet;
	RAD_REQUEST_FUNP fun = NULL;
	RADCLIENT	*client = NULL;
	fr_ipaddr_t	src_ipaddr;

	rcode = rad_recv_header(listener->fd, &src_ipaddr, &src_port, &code);
	if (rcode < 0) return 0;

	FR_STATS_INC(auth, total_requests);

	if (rcode < 20) {
		FR_STATS_INC(auth, total_malformed_requests);
		return 0;
	}

	if ((client = client_listener_find(listener,
					   &src_ipaddr, src_port)) == NULL) {
		rad_recv_discard(listener->fd);
		FR_STATS_INC(auth, total_invalid_requests);
		return 0;
	}

	FR_STATS_TYPE_INC(client->auth.total_requests);


	switch(code) {
	case PW_AUTHENTICATION_REQUEST:
		fun = rad_authenticate;
		break;

	case PW_STATUS_SERVER:
		if (!mainconfig.status_server) {
			rad_recv_discard(listener->fd);
			FR_STATS_INC(auth, total_unknown_types);
			DEBUG("WARNING: Ignoring Status-Server request due to security configuration");
			return 0;
		}
		fun = rad_status_server;
		break;

	default:
		rad_recv_discard(listener->fd);
		FR_STATS_INC(auth,total_unknown_types);

		DEBUG("Invalid packet code %d sent to authentication port from client %s port %d : IGNORED",
		      code, client->shortname, src_port);
		return 0;
		break;
	}


	packet = rad_recv(listener->fd, client->message_authenticator);
	if (!packet) {
		FR_STATS_INC(auth, total_malformed_requests);
		DEBUG("%s", fr_strerror());
		return 0;
	}

	if (!request_receive(listener, packet, client, fun)) {
		FR_STATS_INC(auth, total_packets_dropped);
		rad_free(&packet);
		return 0;
	}

	return 1;
}
