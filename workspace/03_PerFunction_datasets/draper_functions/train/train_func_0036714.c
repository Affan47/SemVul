fr_packet_list_socket_add(fr_packet_list_t *pl, int sockfd)
{
	int i, start;
	struct sockaddr_storage	src;
	socklen_t	        sizeof_src = sizeof(src);
	fr_packet_socket_t	*ps;

	if (!pl) return 0;

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
		return 0;
	}

	memset(ps, 0, sizeof(*ps));
	ps->sockfd = sockfd;
	ps->offset = start;


	memset(&src, 0, sizeof_src);
	if (getsockname(sockfd, (struct sockaddr *) &src,
			&sizeof_src) < 0) {
		return 0;
	}

	if (!fr_sockaddr2ipaddr(&src, sizeof_src, &ps->ipaddr, &ps->port)) {
		return 0;
	}


	if (src.ss_family == AF_INET) {
		if (ps->ipaddr.ipaddr.ip4addr.s_addr == INADDR_ANY) {
			ps->inaddr_any = 1;
		}

#ifdef HAVE_STRUCT_SOCKADDR_IN6
	} else if (src.ss_family == AF_INET6) {
		if (IN6_IS_ADDR_UNSPECIFIED(&ps->ipaddr.ipaddr.ip6addr)) {
			ps->inaddr_any = 1;
		}
#endif
	} else {
		return 0;
	}

	pl->mask |= (1 << ps->offset);
	return 1;
}
