net_connect(net_t *net)
{
	struct pollfd pfd;
	int           sockfd, cs, err = 0;
	socklen_t     err_len = sizeof(err);

	if (net == NULL || net->srv == NULL) {
		DBG_NULL;
		return KNOT_EINVAL;
	}


	get_addr_str((struct sockaddr_storage *)net->srv->ai_addr,
	             net->socktype, &net->remote_str);


	sockfd = socket(net->srv->ai_family, net->socktype, 0);
	if (sockfd == -1) {
		WARN("can't create socket for %s\n", net->remote_str);
		return KNOT_NET_ESOCKET;
	}


	pfd.fd = sockfd;
	pfd.events = POLLOUT;
	pfd.revents = 0;


	if (fcntl(sockfd, F_SETFL, O_NONBLOCK) == -1) {
		WARN("can't set non-blocking socket for %s\n", net->remote_str);
		return KNOT_NET_ESOCKET;
	}


	if (net->local_info != NULL) {

		get_addr_str((struct sockaddr_storage *)net->local_info->ai_addr,
		             net->socktype, &net->local_str);

		if (bind(sockfd, net->local_info->ai_addr,
		         net->local_info->ai_addrlen) == -1) {
			WARN("can't assign address %s\n", net->local_str);
			return KNOT_NET_ESOCKET;
		}
	}

	if (net->socktype == SOCK_STREAM) {

		if (connect(sockfd, net->srv->ai_addr, net->srv->ai_addrlen)
		    == -1 && errno != EINPROGRESS) {
			WARN("can't connect to %s\n", net->remote_str);
			close(sockfd);
			return KNOT_NET_ECONNECT;
		}


		if (poll(&pfd, 1, 1000 * net->wait) != 1) {
			WARN("connection timeout for %s\n", net->remote_str);
			close(sockfd);
			return KNOT_NET_ECONNECT;
		}


		cs = getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &err, &err_len);
		if (cs < 0 || err != 0) {
			WARN("can't connect to %s\n", net->remote_str);
			close(sockfd);
			return KNOT_NET_ECONNECT;
		}
	}


	net->sockfd = sockfd;

	return KNOT_EOK;
}
