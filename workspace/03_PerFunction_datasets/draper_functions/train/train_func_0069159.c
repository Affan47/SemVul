connect_host (kx_context *kc)
{
    struct addrinfo *ai, *a;
    struct addrinfo hints;
    int error;
    char portstr[NI_MAXSERV];
    socklen_t addrlen;
    int s = -1;
    struct sockaddr_storage thisaddr_ss;
    struct sockaddr *thisaddr = (struct sockaddr *)&thisaddr_ss;

    memset (&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    snprintf (portstr, sizeof(portstr), "%u", ntohs(kc->port));

    error = getaddrinfo (kc->host, portstr, &hints, &ai);
    if (error) {
	warnx ("%s: %s", kc->host, gai_strerror(error));
	return -1;
    }

    for (a = ai; a != NULL; a = a->ai_next) {
	s = socket (a->ai_family, a->ai_socktype, a->ai_protocol);
	if (s < 0)
	    continue;
	if (connect (s, a->ai_addr, a->ai_addrlen) < 0) {
	    warn ("connect(%s)", kc->host);
	    close (s);
	    continue;
	}
	break;
    }

    if (a == NULL) {
	freeaddrinfo (ai);
	return -1;
    }

    addrlen = sizeof(thisaddr_ss);
    if (getsockname (s, thisaddr, &addrlen) < 0 ||
	addrlen != a->ai_addrlen)
	err(1, "getsockname(%s)", kc->host);
    memcpy (&kc->__ss_this, thisaddr, sizeof(kc->__ss_this));
    kc->thisaddr_len = addrlen;
    memcpy (&kc->__ss_that, a->ai_addr, sizeof(kc->__ss_that));
    kc->thataddr_len = a->ai_addrlen;
    freeaddrinfo (ai);
    if ((*kc->authenticate)(kc, s))
	return -1;
    return s;
}
