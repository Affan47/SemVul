fr_packet_list_socket_add(fr_packet_list_t *pl, int sockfd, int proto,
			      fr_ipaddr_t *dst_ipaddr, int dst_port,
			      void *ctx)
{
	int i, start;
	struct sockaddr_storage	src;
	socklen_t	        sizeof_src;
	fr_packet_socket_t	*ps;

	if (!pl || !dst_ipaddr || (dst_ipaddr->af == AF_UNSPEC)) {
		fr_strerror_printf("Invalid argument");
		return 0;
	}

	if (pl->num_sockets >= MAX_SOCKETS) {
		fr_strerror_printf("Too many open sockets");
		return 0;
	}

#ifndef WITH_TCP
	if (proto != IPPROTO_UDP) {
		fr_strerror_printf("only UDP is supported");
		return 0;
	}
#endif

	ps = NULL;
	i = start = SOCK2OFFSET(sockfd);

	do {
		if (pl->sockets[i].sockfd == -1) {
			ps =  &pl->sockets[i];
			start = i;
			break;
		}

		i = (i + 1) & SOCKOFFSET_MASK;
	} while (i != start);

	if (!ps) {
		fr_strerror_printf("All socket entries are full");
		return 0;
	}

	memset(ps, 0, sizeof(*ps));
	ps->ctx = ctx;
#ifdef WITH_TCP
	ps->proto = proto;
#endif


	sizeof_src = sizeof(src);
	memset(&src, 0, sizeof_src);
	if (getsockname(sockfd, (struct sockaddr *) &src,
			&sizeof_src) < 0) {
		fr_strerror_printf("%s", strerror(errno));
		return 0;
	}

	if (!fr_sockaddr2ipaddr(&src, sizeof_src, &ps->src_ipaddr,
				&ps->src_port)) {
		fr_strerror_printf("Failed to get IP");
		return 0;
	}

	ps->dst_ipaddr = *dst_ipaddr;
	ps->dst_port = dst_port;

	ps->src_any = fr_inaddr_any(&ps->src_ipaddr);
	if (ps->src_any < 0) return 0;

	ps->dst_any = fr_inaddr_any(&ps->dst_ipaddr);
	if (ps->dst_any < 0) return 0;


	ps->sockfd = sockfd;
	pl->num_sockets++;

	return 1;
}
