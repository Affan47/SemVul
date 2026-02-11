ConnectTo(const char* host, int _port, uintptr_t opaque)
{
    char port[16];
    sprintf(port, "%d", _port);

    int sock;
    int status = 0;

    struct addrinfo* ai_ptr = NULL;
    ai_ptr = AllocSocketFd(&TryConnectTo, host, port, &sock, &status);
    if (sock < 0 || ai_ptr == NULL) return NULL;


    SocketConnection* new_sock = SetupSocketConnection(sock, opaque, true);

    if (status == 0)
    {

        struct sockaddr* addr = ai_ptr->ai_addr;
        void* sin_addr = (ai_ptr->ai_family == AF_INET)?
            (void*)&((struct sockaddr_in*)addr)->sin_addr:
            (void*)&((struct sockaddr_in6*)addr)->sin6_addr;

        inet_ntop(ai_ptr->ai_family, sin_addr, new_sock->buff_, sizeof(new_sock->buff_));

        new_sock->status_ = SS_CONNECTED;
    }
    else
    {
        new_sock->status_ = SS_CONNECTING;


        poller_.ModifySocket(new_sock->fd_, new_sock, true);
    }

    return new_sock;
}
