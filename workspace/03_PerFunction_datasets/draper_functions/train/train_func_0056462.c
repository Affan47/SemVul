ipv6_open_server_sock(IrmoNetModule *module,
                                            unsigned int port)
{
        SockBaseSocket *result;
        struct sockaddr_in6 addr;
        socklen_t addr_len;
        int status;

        result = irmo_sockbase_open(&ipv6_socket_class, AF_INET6);

        if (result == NULL) {
                return NULL;
        }


        addr_len = sizeof(struct sockaddr_in6);
        addr.sin6_family = AF_INET;
        memcpy(&addr.sin6_addr, &in6addr_any, sizeof(struct in6_addr));
        addr.sin6_port = htons((uint16_t) port);

        status = bind(result->sock, (struct sockaddr *) &addr, addr_len);

        if (status < 0) {
                irmo_error_report("ipv6_open_server_sock",
                                  "Cannot bind to port %i (%s)",
                                  port, strerror(errno));
                closesocket(result->sock);
                free(result);
                return NULL;
        }

        return &result->irmo_socket;
}
