changeMcastMembership(struct socklist *s, struct socklist *g, int op)
{
    int sockopt;

    switch (s->addr->sa_family) {
    case AF_INET: {
        struct ip_mreq mreq;
        memcpy(&mreq.imr_multiaddr,
               &((struct sockaddr_in *)g->addr)->sin_addr,
               sizeof(struct in_addr));
        memcpy(&mreq.imr_interface,
               &((struct sockaddr_in *)s->addr)->sin_addr,
               sizeof(struct in_addr));
        if (op == JOIN_MCAST_GROUP)
            sockopt = IP_ADD_MEMBERSHIP;
        else
            sockopt = IP_DROP_MEMBERSHIP;
        if (setsockopt(s->fd, IPPROTO_IP, sockopt,
                       &mreq, sizeof(mreq)) < 0)
        {
            logError("XDMCP socket multicast %s to %s failed, errno %d\n",
                     (op == JOIN_MCAST_GROUP) ? "join" : "drop",
                     inet_ntoa(((struct sockaddr_in *)g->addr)->sin_addr),
                     errno);
        } else if (debugLevel & DEBUG_CORE) {
            debug("XDMCP socket multicast %s to %s succeeded\n",
                  (op == JOIN_MCAST_GROUP) ? "join" : "drop",
                  inet_ntoa(((struct sockaddr_in *)g->addr)->sin_addr));
        }
        return; }
#if defined(IPv6) && defined(AF_INET6)
# ifndef IPV6_JOIN_GROUP
#  define IPV6_JOIN_GROUP IPV6_ADD_MEMBERSHIP
# endif
# ifndef IPV6_LEAVE_GROUP
#  define IPV6_LEAVE_GROUP IPV6_DROP_MEMBERSHIP
# endif
    case AF_INET6: {
        struct ipv6_mreq mreq6;
        memcpy(&mreq6.ipv6mr_multiaddr,
               &((struct sockaddr_in6 *)g->addr)->sin6_addr,
               sizeof(struct in6_addr));
        mreq6.ipv6mr_interface = 0;
        if (op == JOIN_MCAST_GROUP)
            sockopt = IPV6_JOIN_GROUP;
        else
            sockopt = IPV6_LEAVE_GROUP;
        if (setsockopt(s->fd, IPPROTO_IPV6, sockopt,
                       &mreq6, sizeof(mreq6)) < 0)
        {
            int saveerr = errno;
            char addrbuf[INET6_ADDRSTRLEN];

            inet_ntop(s->addr->sa_family,
                      &((struct sockaddr_in6 *)g->addr)->sin6_addr,
                      addrbuf, sizeof(addrbuf));

            logError("XDMCP socket multicast %s to %s failed, errno %d\n",
                     (op == JOIN_MCAST_GROUP) ? "join" : "drop", addrbuf,
                     saveerr);
        } else if (debugLevel & DEBUG_CORE) {
            char addrbuf[INET6_ADDRSTRLEN];

            inet_ntop(s->addr->sa_family,
                      &((struct sockaddr_in6 *)g->addr)->sin6_addr,
                      addrbuf, sizeof(addrbuf));

            debug("XDMCP socket multicast %s to %s succeeded\n",
                  (op == JOIN_MCAST_GROUP) ? "join" : "drop", addrbuf);
        }
        return; }
#endif
    }
}
