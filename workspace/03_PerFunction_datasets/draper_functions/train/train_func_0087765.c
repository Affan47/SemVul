socket_select(t_socket n, fd_set *rfds, fd_set *wfds, fd_set *efds,
        p_timeout tm) {
    int ret;
    do {
        struct timeval tv;
        double t = timeout_getretry(tm);
        tv.tv_sec = (int) t;
        tv.tv_usec = (int) ((t - tv.tv_sec) * 1.0e6);

        ret = select(n, rfds, wfds, efds, t >= 0.0 ? &tv: NULL);
    } while (ret < 0 && errno == EINTR);
    return ret;
}
