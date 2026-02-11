CheckForData( int timeout )
{
    if ( RecvBuf.size() > 0 )
    {
        return true;
    }

    int ret;

    Timeout.tv_sec = timeout;
    Timeout.tv_usec = 0;

    FD_ZERO(&checkfd);
    FD_SET(sock_fd,&checkfd);

    ret = select_eintr(sock_fd+1, &checkfd, NULL, NULL, &Timeout);

    if (ret <= 0)
    {
        return false;
    }

    return true;
}
