init_net(const char *host, char *port,
	     struct protstream **in, struct protstream **out)
{
    int sock = -1, err;
    struct addrinfo hints, *res, *res0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = 0;
    if ((err = getaddrinfo(host, port, &hints, &res0)) != 0) {
	syslog(LOG_ERR, "getaddrinfo(%s, %s) failed: %m", host, port);
	return -1;
    }

    for (res = res0; res; res = res->ai_next) {
	if ((sock = socket(res->ai_family, res->ai_socktype,
			   res->ai_protocol)) < 0)
	    continue;
	if (connect(sock, res->ai_addr, res->ai_addrlen) >= 0)
	    break;
	close(sock);
	sock = -1;
    }
    freeaddrinfo(res0);
    if(sock < 0) {
	syslog(LOG_ERR, "connect(%s:%s) failed: %m", host, port);
	return -1;
    }

    *in = prot_new(sock, 0);
    *out = prot_new(sock, 1);
    prot_setflushonread(*in, *out);

    return sock;
}
