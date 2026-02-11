doPingHosts()
{
    HostAddr *hosts;

    for (hosts = hostAddrdb; hosts; hosts = hosts->next)
#if defined(IPv6) && defined(AF_INET6)
        XdmcpFlush(hosts->addr->sa_family == AF_INET6 ? socket6FD : socketFD,
#else
        XdmcpFlush(socketFD,
#endif
                   hosts->type == QUERY ? &directBuffer : &broadcastBuffer,
                   (XdmcpNetaddr)hosts->addr, hosts->addrlen);
}
