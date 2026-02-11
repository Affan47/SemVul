SockAddr_isMulticast( iperf_sockaddr *inSockAddr ) {

#if defined(HAVE_IPV6)
    if ( ((struct sockaddr*)inSockAddr)->sa_family == AF_INET6 ) {
        return( IN6_IS_ADDR_MULTICAST(&(((struct sockaddr_in6*) inSockAddr)->sin6_addr) ));
    } else
#endif
    {

        const unsigned long kMulticast_Mask = 0xe0000000L;

        return(kMulticast_Mask ==
               (ntohl( ((struct sockaddr_in*) inSockAddr)->sin_addr.s_addr) & kMulticast_Mask));
    }
}
