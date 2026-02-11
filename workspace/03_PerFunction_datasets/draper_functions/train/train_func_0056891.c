network_bind_ipv4(const char *address, unsigned short port)
{
    int fd, bindfd;
    struct sockaddr_in server;
    struct in_addr addr;


    fd = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
    if (fd < 0) {
        syswarn("cannot create IPv4 socket for %s,%hu", address, port);
        return -1;
    }
    network_set_reuseaddr(fd);


    if (!strcmp(address, "any") || !strcmp(address, "all"))
        address = "0.0.0.0";


    if (port < 1024 && geteuid() != 0) {
        bindfd = network_innbind(fd, AF_INET, address, port);
        if (bindfd != fd)
            close(fd);
        return bindfd;
    } else {
        memset(&server, 0, sizeof server);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);
        if (!inet_aton(address, &addr)) {
            warn("invalid IPv4 address %s", address);
            return -1;
        }
        server.sin_addr = addr;
        sin_set_length(&server);
        if (bind(fd, (struct sockaddr *) &server, sizeof(server)) < 0) {
            syswarn("cannot bind socket for %s,%hu", address, port);
            return -1;
        }
        return fd;
    }
}
