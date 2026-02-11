CloseSocket(int fd)
{
    SocketConnection* sock = &sockets_[fd];
    if (sock->status_ == SS_INVALID || sock->fd_ != fd)
    {
        slog(LOG_WARN, "try to close bad socket, fd(%d)", fd);
        return false;
    }

    ForceSocketClose(sock);

    return true;
}
