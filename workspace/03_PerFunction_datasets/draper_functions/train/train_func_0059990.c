network_kill_options(int fd, struct sockaddr *remote)
{
    int status;
    char options[BUFSIZ / 3];
    char addr[INET6_ADDRSTRLEN];
    socklen_t optsize = sizeof(options);

    if (remote->sa_family != AF_INET)
        return true;
    status = getsockopt(fd, IPPROTO_IP, IP_OPTIONS, options, &optsize);
    if (status == 0 && optsize != 0) {
        char hex[BUFSIZ];
        char *opt, *output;

        output = hex;
        for (opt = options; optsize > 0; opt++, optsize--, output += 3)
            snprintf(output, sizeof(hex) - (output - hex), " %2.2x", *opt);
        network_sockaddr_sprint(addr, sizeof(addr), remote);
        notice("connect from %s with IP options (ignored):%s", addr, hex);
        if (setsockopt(fd, IPPROTO_IP, IP_OPTIONS, NULL, 0) != 0) {
            syswarn("setsockopt IP_OPTIONS NULL failed");
            return false;
        }
    }
    return true;
}
