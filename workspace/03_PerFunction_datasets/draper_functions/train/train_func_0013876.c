__socket_nodelay (int fd)
{
        int     on = 1;
        int     ret = -1;

        ret = setsockopt (fd, IPPROTO_TCP, TCP_NODELAY,
                          &on, sizeof (on));
        if (!ret)
                gf_log (THIS->name, GF_LOG_TRACE,
                        "NODELAY enabled for socket %d", fd);

        return ret;
}
