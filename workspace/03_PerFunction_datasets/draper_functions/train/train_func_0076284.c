internal_select_ex(PySocketSockObject *s, int writing, double interval)
{
    int n;


    if (s->sock_timeout <= 0.0)
        return 0;


    if (s->sock_fd < 0)
        return 0;


    if (interval < 0.0)
        return 1;


#ifdef HAVE_POLL
    {
        struct pollfd pollfd;
        int timeout;

        pollfd.fd = s->sock_fd;
        pollfd.events = writing ? POLLOUT : POLLIN;


        timeout = (int)(interval * 1000 + 0.5);
        n = poll(&pollfd, 1, timeout);
    }
#else
    {

        fd_set fds;
        struct timeval tv;
        tv.tv_sec = (int)interval;
        tv.tv_usec = (int)((interval - tv.tv_sec) * 1e6);
        FD_ZERO(&fds);
        FD_SET(s->sock_fd, &fds);


        if (writing)
            n = select(Py_SAFE_DOWNCAST(s->sock_fd+1, SOCKET_T, int),
                       NULL, &fds, NULL, &tv);
        else
            n = select(Py_SAFE_DOWNCAST(s->sock_fd+1, SOCKET_T, int),
                       &fds, NULL, NULL, &tv);
    }
#endif

    if (n < 0)
        return -1;
    if (n == 0)
        return 1;
    return 0;
}
