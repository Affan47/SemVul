__socket_connect_finish (int fd)
{
        int       ret = -1;
        int       optval = 0;
        socklen_t optlen = sizeof (int);

        ret = getsockopt (fd, SOL_SOCKET, SO_ERROR, (void *)&optval, &optlen);

        if (ret == 0 && optval) {
                errno = optval;
                ret = -1;
        }

        return ret;
}
