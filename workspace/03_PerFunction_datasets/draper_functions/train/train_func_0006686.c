tcp_create_listen_sock(struct connection *con,
					     struct sockaddr_storage *saddr)
{
	struct socket *sock = NULL;
	int result = 0;
	int one = 1;
	int addr_len;

	if (dlm_local_addr[0]->ss_family == AF_INET)
		addr_len = sizeof(struct sockaddr_in);
	else
		addr_len = sizeof(struct sockaddr_in6);


	result = sock_create_kern(&init_net, dlm_local_addr[0]->ss_family,
				  SOCK_STREAM, IPPROTO_TCP, &sock);
	if (result < 0) {
		log_print("Can't create listening comms socket");
		goto create_out;
	}


	kernel_setsockopt(sock, SOL_TCP, TCP_NODELAY, (char *)&one,
			  sizeof(one));

	result = kernel_setsockopt(sock, SOL_SOCKET, SO_REUSEADDR,
				   (char *)&one, sizeof(one));

	if (result < 0) {
		log_print("Failed to set SO_REUSEADDR on socket: %d", result);
	}
	con->rx_action = tcp_accept_from_sock;
	con->connect_action = tcp_connect_to_sock;


	make_sockaddr(saddr, dlm_config.ci_tcp_port, &addr_len);
	result = sock->ops->bind(sock, (struct sockaddr *) saddr, addr_len);
	if (result < 0) {
		log_print("Can't bind to port %d", dlm_config.ci_tcp_port);
		sock_release(sock);
		sock = NULL;
		con->sock = NULL;
		goto create_out;
	}
	result = kernel_setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE,
				 (char *)&one, sizeof(one));
	if (result < 0) {
		log_print("Set keepalive failed: %d", result);
	}

	result = sock->ops->listen(sock, 5);
	if (result < 0) {
		log_print("Can't listen on port %d", dlm_config.ci_tcp_port);
		sock_release(sock);
		sock = NULL;
		goto create_out;
	}

create_out:
	return sock;
}
