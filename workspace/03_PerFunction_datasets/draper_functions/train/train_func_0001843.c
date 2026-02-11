isns_get_ip(int fd)
{
	int err, i;
	uint32_t addr;
	union {
		struct sockaddr s;
		struct sockaddr_storage ss;
		struct sockaddr_in s4;
		struct sockaddr_in6 s6;
	} l;
	socklen_t slen = sizeof(l.s);

	err = getsockname(fd, &l.s, &slen);
	if (err) {
		log_error("getsockname error %s!", gai_strerror(err));
		return err;
	}

	err = getnameinfo(&l.s, sizeof(l.s),
			  eid, sizeof(eid), NULL, 0, 0);
	if (err) {
		log_error("getaddrinfo error %s!", gai_strerror(err));
		return err;
	}

	switch (l.ss.ss_family) {
	case AF_INET:
		addr = ((&l.s4)->sin_addr.s_addr);

		ip[10] = ip[11] = 0xff;
		ip[15] = 0xff & (addr >> 24);
		ip[14] = 0xff & (addr >> 16);
		ip[13] = 0xff & (addr >> 8);
		ip[12] = 0xff & addr;
		break;
	case AF_INET6:
		for (i = 0; i < ARRAY_SIZE(ip); i++)
			ip[i] = (&l.s6)->sin6_addr.s6_addr[i];
		break;
	}

	return 0;
}
