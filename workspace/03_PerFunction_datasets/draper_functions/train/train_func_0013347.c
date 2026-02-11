is_af_unix_keeper(const int fd)
{
    struct pollfd pfd;
    pfd.fd = fd;
    pfd.events = POLLIN;

    return poll(&pfd, 1, libfcgiIsAfUnixKeeperPollTimeout) >= 0 && (pfd.revents & POLLIN);
}
