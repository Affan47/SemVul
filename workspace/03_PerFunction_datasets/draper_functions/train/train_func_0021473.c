sb_verbose_accept(int listen_socket)
{
    union {
        struct sockaddr_in sin;
        struct sockaddr_in6 sin6;
    } client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char client_addr_str[INET6_ADDRSTRLEN];

    int client = accept(listen_socket, (struct sockaddr *)&client_addr,
                        &client_addr_len);
    if(client < 0)
        SB_PRINT_ERR_DIE("accept() failed")

    if(fcntl(client, F_SETFL, O_NONBLOCK) < 0)
        SB_PRINT_ERR_DIE("Setting nonblocking I/O failed")


    printf("Connection from %s\n",
           inet_ntop(client_addr.sin.sin_family,
                     client_addr.sin.sin_family == AF_INET
                        ? (const void *)&client_addr.sin.sin_addr
                        : (const void *)&client_addr.sin6.sin6_addr,
                     client_addr_str, sizeof(client_addr_str)));

    return client;
}
