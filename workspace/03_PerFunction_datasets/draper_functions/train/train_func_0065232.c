make_netsocket(u_short port, char *host, int type)
{
	int s, flag = 1;
	struct sockaddr_in sa;
	struct in_addr *saddr;
	int socket_type;


	socket_type = (type == NETSOCKET_UDP) ? SOCK_DGRAM : SOCK_STREAM;

	bzero((void *)&sa, sizeof(struct sockaddr_in));

	if ((s = socket(AF_INET, socket_type, 0)) < 0)
		return (-1);
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (char *)&flag,
			sizeof(flag)) < 0)
		return (-1);

	saddr = make_addr(host);
	if (saddr == NULL && type != NETSOCKET_UDP)
		return (-1);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(port);

	if (type == NETSOCKET_SERVER) {

		if (host != NULL)
			sa.sin_addr.s_addr = saddr->s_addr;

		if (bind(s, (struct sockaddr *)&sa, sizeof sa) < 0) {
			close(s);
			return (-1);
		}
	}
	if (type == NETSOCKET_CLIENT) {
		sa.sin_addr.s_addr = saddr->s_addr;
		if (connect(s, (struct sockaddr *)&sa, sizeof sa) < 0) {
			close(s);
			return (-1);
		}
	}
	if (type == NETSOCKET_UDP) {

		if (bind(s, (struct sockaddr *)&sa, sizeof sa) < 0) {
			close(s);
			return (-1);
		}


		if (host != NULL && saddr != NULL) {
			sa.sin_addr.s_addr = saddr->s_addr;
			if (connect(s, (struct sockaddr *)&sa, sizeof sa) < 0) {
				close(s);
				return (-1);
			}
		}
	}

	return (s);
}
