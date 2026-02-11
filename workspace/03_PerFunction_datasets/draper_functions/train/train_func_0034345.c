resolve_ip_hostname (sockaddr_storage *addr_, socklen_t *addr_len_,
    const char *hostname_)
{

    const char *delimiter = strchr (hostname_, ':');
    if (!delimiter) {
        errno = EINVAL;
        return -1;
    }


    std::string hostname (hostname_, delimiter - hostname_);
    std::string service (delimiter + 1);


    addrinfo req;
    memset (&req, 0, sizeof (req));


    req.ai_family = AF_INET;


    req.ai_socktype = SOCK_STREAM;


    req.ai_flags = AI_NUMERICSERV;


    addrinfo *res;
    int rc = getaddrinfo (hostname.c_str (), service.c_str (), &req, &res);
    if (rc) {
        errno = EINVAL;
        return -1;
    }


    zmq_assert ((size_t) (res->ai_addrlen) <= sizeof (*addr_));
    memcpy (addr_, res->ai_addr, res->ai_addrlen);
    *addr_len_ = res->ai_addrlen;

    freeaddrinfo (res);

    return 0;
}
