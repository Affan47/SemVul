AllocSocketFd(SocketPredicateProc proc,
                                      const char* host, const char* port,
                                      int* sfd, int* stat)
{
    int status;
    int sock = -1;
    struct addrinfo ai_hints;
    struct addrinfo *ai_list = NULL;
    struct addrinfo *ai_ptr  = NULL;

    memset(&ai_hints, 0, sizeof(ai_hints));
    ai_hints.ai_family   = AF_UNSPEC;
    ai_hints.ai_socktype = SOCK_STREAM;
    ai_hints.ai_protocol = IPPROTO_TCP;

    status = getaddrinfo(host, port, &ai_hints, &ai_list);
    if (status) goto _failed;

    for (ai_ptr = ai_list; ai_ptr != NULL; ai_ptr = ai_ptr->ai_next)
    {
#ifdef SOCK_NONBLOCK
        sock = socket(ai_ptr->ai_family, ai_ptr->ai_socktype | SOCK_NONBLOCK, ai_ptr->ai_protocol);
        if (sock < 0) continue;
#else
        sock = socket(ai_ptr->ai_family, ai_ptr->ai_socktype, ai_ptr->ai_protocol);
        if (sock < 0) continue;
        SocketPoll::SetSocketNonBlocking(sock);
#endif

        status = proc(sock, ai_ptr);
        if (status >= 0) break;

        close(sock);
        sock = -1;
    }

    if (sock < 0) goto _failed;
    if (sfd) *sfd = sock;
    if (stat) *stat = status;

    return ai_ptr;

_failed:

    slog(LOG_ERROR, "alloc socket fd fail, target:host(%s),port(%s)\n", host, port);
    freeaddrinfo(ai_list);
    return NULL;
}
