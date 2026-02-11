connect_addr(struct addrinfo *addr, const char* cnx_name)
{
    struct addrinfo *a;
    char buf[NI_MAXHOST];
    int fd, res;

    for (a = addr; a; a = a->ai_next) {
        if (verbose)
            fprintf(stderr, "connecting to %s family %d len %d\n",
                    sprintaddr(buf, sizeof(buf), a),
                    a->ai_addr->sa_family, a->ai_addrlen);
        fd = socket(a->ai_family, SOCK_STREAM, 0);
        if (fd == -1) {
            log_message(LOG_ERR, "forward to %s failed:socket: %s\n", cnx_name, strerror(errno));
        } else {
            res = connect(fd, a->ai_addr, a->ai_addrlen);
            if (res == -1) {
                log_message(LOG_ERR, "forward to %s failed:connect: %s\n",
                            cnx_name, strerror(errno));
            } else {
                return fd;
            }
        }
    }
    return -1;
}
