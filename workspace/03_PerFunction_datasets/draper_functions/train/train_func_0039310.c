evutil_check_interfaces(int force_recheck)
{
	const char ZEROES[] = "\x00\x00\x00\x00\x00\x00\x00\x00"
	    "\x00\x00\x00\x00\x00\x00\x00\x00";
	evutil_socket_t fd = -1;
	struct sockaddr_in sin, sin_out;
	struct sockaddr_in6 sin6, sin6_out;
	ev_socklen_t sin_out_len = sizeof(sin_out);
	ev_socklen_t sin6_out_len = sizeof(sin6_out);
	int r;
	char buf[128];
	if (have_checked_interfaces && !force_recheck)
		return 0;


	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(53);
	r = evutil_inet_pton(AF_INET, "18.244.0.188", &sin.sin_addr);
	EVUTIL_ASSERT(r);

	memset(&sin6, 0, sizeof(sin6));
	sin6.sin6_family = AF_INET6;
	sin6.sin6_port = htons(53);
	r = evutil_inet_pton(AF_INET6, "2001:4860:b002::68", &sin6.sin6_addr);
	EVUTIL_ASSERT(r);

	memset(&sin_out, 0, sizeof(sin_out));
	memset(&sin6_out, 0, sizeof(sin6_out));


	if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) >= 0 &&
	    connect(fd, (struct sockaddr*)&sin, sizeof(sin)) == 0 &&
	    getsockname(fd, (struct sockaddr*)&sin_out, &sin_out_len) == 0) {

		ev_uint32_t addr = ntohl(sin_out.sin_addr.s_addr);
		if (addr == 0 ||
		    EVUTIL_V4ADDR_IS_LOCALHOST(addr) ||
		    EVUTIL_V4ADDR_IS_CLASSD(addr)) {
			evutil_inet_ntop(AF_INET, &sin_out.sin_addr,
			    buf, sizeof(buf));


			event_warnx("Got a strange local ipv4 address %s",buf);
		} else {
			event_debug(("Detected an IPv4 interface"));
			had_ipv4_address = 1;
		}
	}
	if (fd >= 0)
		evutil_closesocket(fd);

	if ((fd = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP)) >= 0 &&
	    connect(fd, (struct sockaddr*)&sin6, sizeof(sin6)) == 0 &&
	    getsockname(fd, (struct sockaddr*)&sin6_out, &sin6_out_len) == 0) {

		const unsigned char *addr =
		    (unsigned char*)sin6_out.sin6_addr.s6_addr;
		if (!memcmp(addr, ZEROES, 8) ||
		    (addr[0] == 0xfe && (addr[1] & 0xc0) == 0x80)) {


			evutil_inet_ntop(AF_INET6, &sin6_out.sin6_addr,
			    buf, sizeof(buf));
			event_warnx("Got a strange local ipv6 address %s",buf);
		} else {
			event_debug(("Detected an IPv4 interface"));
			had_ipv6_address = 1;
		}
	}

	if (fd >= 0)
		evutil_closesocket(fd);

	return 0;
}
