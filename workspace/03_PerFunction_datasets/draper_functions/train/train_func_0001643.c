udp_make(struct sockaddr *laddr)
{
	struct udp_transport *t = 0;
	int	s, on, wildcardaddress = 0;
	char	*tstr;

	t = calloc(1, sizeof *t);
	if (!t) {
		log_print("udp_make: calloc (1, %lu) failed",
		    (unsigned long)sizeof *t);
		free(laddr);
		return 0;
	}
	t->src = laddr;

	s = socket(laddr->sa_family, SOCK_DGRAM, IPPROTO_UDP);
	if (s == -1) {
		log_error("udp_make: socket (%d, %d, %d)", laddr->sa_family,
		    SOCK_DGRAM, IPPROTO_UDP);
		goto err;
	}

	if (sysdep_cleartext(s, laddr->sa_family) == -1)
		goto err;


	switch (laddr->sa_family) {
	case AF_INET:
		if (((struct sockaddr_in *)laddr)->sin_addr.s_addr ==
		    INADDR_ANY)
			wildcardaddress = 1;
		break;
	case AF_INET6:
		if (IN6_IS_ADDR_UNSPECIFIED(&((struct sockaddr_in6 *)laddr)->sin6_addr))
			wildcardaddress = 1;
		break;
	}


	on = 1;
	if (setsockopt(s, SOL_SOCKET,
	    wildcardaddress ? SO_REUSEPORT : SO_REUSEADDR,
	    (void *)&on, sizeof on) == -1) {
		log_error("udp_make: setsockopt (%d, %d, %d, %p, %lu)", s,
		    SOL_SOCKET, wildcardaddress ? SO_REUSEPORT : SO_REUSEADDR,
		    &on, (unsigned long)sizeof on);
		goto err;
	}
	t->transport.vtbl = &udp_transport_vtbl;
	if (monitor_bind(s, t->src, sysdep_sa_len(t->src))) {
		if (sockaddr2text(t->src, &tstr, 0))
			log_error("udp_make: bind (%d, %p, %lu)", s, &t->src,
			    (unsigned long)sizeof t->src);
		else {
			log_error("udp_make: bind (%d, %s, %lu)", s, tstr,
			    (unsigned long)sizeof t->src);
			free(tstr);
		}
		goto err;
	}
	t->s = s;
	if (sockaddr2text(t->src, &tstr, 0))
		LOG_DBG((LOG_MISC, 20, "udp_make: "
		    "transport %p socket %d family %d", t, s,
		    t->src->sa_family == AF_INET ? 4 : 6));
	else {
		LOG_DBG((LOG_MISC, 20, "udp_make: "
		    "transport %p socket %d ip %s port %d", t, s,
		    tstr, ntohs(sockaddr_port(t->src))));
		free (tstr);
	}
	transport_setup(&t->transport, 0);
	t->transport.flags |= TRANSPORT_LISTEN;
	return &t->transport;

err:
	if (s >= 0)
		close(s);
	if (t) {

		t->s = -1;
		udp_remove(&t->transport);
	}
	return 0;
}
