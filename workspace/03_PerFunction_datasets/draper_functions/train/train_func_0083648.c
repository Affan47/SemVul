ne_addr_resolve(const char *hostname, int flags)
{
    ne_sock_addr *addr = ne_calloc(sizeof *addr);
#ifdef USE_GETADDRINFO
    struct addrinfo hints = {0};
    char *pnt;
    hints.ai_socktype = SOCK_STREAM;
    if (hostname[0] == '[' && ((pnt = strchr(hostname, ']')) != NULL)) {
	char *hn = ne_strdup(hostname + 1);
	hn[pnt - hostname - 1] = '\0';
#ifdef AI_NUMERICHOST
	hints.ai_flags = AI_NUMERICHOST;
#endif
        hints.ai_family = AF_INET6;
	addr->errnum = getaddrinfo(hn, NULL, &hints, &addr->result);
	ne_free(hn);
    } else {
#ifdef USE_GAI_ADDRCONFIG
        hints.ai_flags = AI_ADDRCONFIG;
        hints.ai_family = AF_UNSPEC;
        addr->errnum = getaddrinfo(hostname, NULL, &hints, &addr->result);
#else
        hints.ai_family = ipv6_disabled ? AF_INET : AF_UNSPEC;
	addr->errnum = getaddrinfo(hostname, NULL, &hints, &addr->result);
#endif
    }
#else
    in_addr_t laddr;
    struct hostent *hp;

    laddr = inet_addr(hostname);
    if (laddr == INADDR_NONE) {
	hp = gethostbyname(hostname);
	if (hp == NULL) {
#ifdef WIN32
	    addr->errnum = WSAGetLastError();
#else
            addr->errnum = h_errno;
#endif
	} else if (hp->h_length != sizeof(struct in_addr)) {

	    addr->errnum = NO_RECOVERY;
	} else {
	    size_t n;

	    for (n = 0; hp->h_addr_list[n] != NULL; n++)
		;

	    addr->count = n;
	    addr->addrs = ne_malloc(n * sizeof *addr->addrs);

	    for (n = 0; n < addr->count; n++)
		memcpy(&addr->addrs[n], hp->h_addr_list[n], hp->h_length);
	}
    } else {
	addr->addrs = ne_malloc(sizeof *addr->addrs);
	addr->count = 1;
	memcpy(addr->addrs, &laddr, sizeof *addr->addrs);
    }
#endif
    return addr;
}
