friendlier_hostname(const char *addr_str, int port)
{
    struct addrinfo hints = { };
    struct addrinfo *res = NULL;
    char hostname[NI_MAXHOST];
    char service[NI_MAXSERV];
    char port_str[6];

    if (!addr_str[0]) return g_strdup("");

    snprintf(port_str, sizeof port_str, "%d", port);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(addr_str, port_str, &hints, &res))
        goto failsafe;

    if (getnameinfo(res->ai_addr, res->ai_addrlen, hostname,
                    sizeof hostname, service, sizeof service, NI_IDN))
        goto failsafe;

    if (res) freeaddrinfo(res);
    return g_strdup_printf("%s, TCP port %d (%s)", hostname, port, service);

  failsafe:
    if (res) freeaddrinfo(res);
    return g_strdup_printf("%s, TCP port %d", addr_str, port);
}
