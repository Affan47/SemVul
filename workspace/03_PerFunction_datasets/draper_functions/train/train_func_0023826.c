setupMitmAttach(uint16_t port)
{
    int fd = -1;
    const int on = 1;

    struct sockaddr_in ssin;

    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        runtime_exception("unable to open socket");

    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof (int));

    memset(&ssin, 0, sizeof (struct sockaddr_in));
    ssin.sin_family = AF_INET;
    ssin.sin_port = htons(port);
    if (!inet_aton(conf.listen_ip, (struct in_addr *) &ssin.sin_addr.s_addr))
        runtime_exception("invalid listening address provided");

    if (bind(fd, (struct sockaddr *) &ssin, sizeof (struct sockaddr_in)) == -1)
        runtime_exception("unable to bind");

    if (listen(fd, 0) == -1)
        runtime_exception("unable to listen");

    return fd;
}
