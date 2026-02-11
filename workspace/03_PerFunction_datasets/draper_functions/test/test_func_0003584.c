netaddrPort(char *netaddrp, int *lenp)
{
#ifdef STREAMSCONN
    *lenp = 2;
    return netaddrp + 2;
#else
    switch (netaddrFamily(netaddrp)) {
    case AF_INET:
        *lenp = 2;
        return (CARD8 *)&(((struct sockaddr_in *)netaddrp)->sin_port);
#if defined(IPv6) && defined(AF_INET6)
    case AF_INET6:
        *lenp = 2;
        return (CARD8 *)&(((struct sockaddr_in6 *)netaddrp)->sin6_port);
#endif
    default:
        *lenp = 0;
        return 0;
    }
#endif
}
