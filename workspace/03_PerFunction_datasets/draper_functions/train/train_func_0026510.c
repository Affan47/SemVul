ListenTo(const char* host, int _port)
{
    int status = 0;
    int listen_fd = -1;
    struct addrinfo* ai_ptr = NULL;

    char port[16];
    sprintf(port, "%d", _port);

    ai_ptr = AllocSocketFd(&TryListenTo, host, port, &listen_fd, &status);
    if (listen_fd < 0 || ai_ptr == NULL) return -1;

    return listen_fd;
}
