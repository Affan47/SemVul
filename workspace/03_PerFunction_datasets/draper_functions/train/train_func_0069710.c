openDataConn(const char* mode, int& code)
{
    byte_count = 0;
    if (pdata >= 0) {
        struct sockaddr_in from;
        socklen_t fromlen = sizeof (from);

        int s = Socket::accept(pdata, (struct sockaddr*) &from, &fromlen);
        if (s < 0) {
            reply(425, "Cannot open data connection.");
            (void) Sys::close(pdata);
            pdata = -1;
            return (NULL);
        }

        (void) Sys::close(pdata);
        pdata = s;
#ifdef IPTOS_LOWDELAY
        int tos = IPTOS_LOWDELAY;
        (void) Socket::setsockopt(s, IPPROTO_IP, IP_TOS, &tos, sizeof (tos));

#endif
	code = 150;
        return (fdopen(pdata, mode));
    }
    if (data >= 0) {
	code = 125;
        usedefault = 1;
        return (fdopen(data, mode));
    }
    if (usedefault)
        data_dest = peer_addr;
    usedefault = 1;
    FILE* file = getDataSocket(mode);
    if (file == NULL) {
        reply(425, "Cannot create data socket (%s,%d): %s.",
              inet_ntoa(data_source.in.sin_addr),
              ntohs(data_source.in.sin_port), strerror(errno));
	return (NULL);
    }
    data = fileno(file);
    for (int swait = 0; !dataConnect(); swait += swaitint) {
	if (!(errno == EADDRINUSE || errno == EINTR) || swait >= swaitmax) {
	    perror_reply(425, "Cannot build data connection", errno);
	    fclose(file);
	    data = -1;
	    return (NULL);
	}
	sleep(swaitint);
    }
    code = 150;
    return (file);
}
