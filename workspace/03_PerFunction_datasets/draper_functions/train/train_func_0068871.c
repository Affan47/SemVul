pollPortScanner(struct PortScanner *ps)
{
    int i, rc, sockerror;
    socklen_t errlen;
    struct pollfd *pfds = ps->sockets;

    launchConnects(ps);
    if (ps->socketCount == 0)
        return 0;
    rc = poll(ps->sockets, ps->socketCount, -1);
    if (rc == -1) {
        if (errno != EINTR) {
            printf("poll failed: %s\n", strerror(errno));
            return 0;
        } else {
            return 1;
        }
    }
    for (i = ps->socketCount; i--;) {
        if (pfds[i].revents & (POLLOUT|POLLERR)) {
            errlen = sizeof sockerror;
            if (getsockopt(pfds[i].fd, SOL_SOCKET, SO_ERROR, &sockerror, &errlen) != 0)
                err(-1, "getsockopt(SO_ERROR)");
            finish(ps, pfds[i].fd, ps->connections[i], sockerror);
            --ps->socketCount;
            pfds[i] = pfds[ps->socketCount];
            ps->connections[i] = ps->connections[ps->socketCount];
            rc--;
        }
    }
    return 1;
}
