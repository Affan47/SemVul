netsnmp_udpbase_recv(netsnmp_transport *t, void *buf, int size,
                     void **opaque, int *olength)
{
    int             rc = -1;
    socklen_t       fromlen = sizeof(struct sockaddr);
    netsnmp_indexed_addr_pair *addr_pair = NULL;
    struct sockaddr *from;

    if (t != NULL && t->sock >= 0) {
        addr_pair = (netsnmp_indexed_addr_pair *) malloc(sizeof(netsnmp_indexed_addr_pair));
        if (addr_pair == NULL) {
            *opaque = NULL;
            *olength = 0;
            return -1;
        } else {
            memset(addr_pair, 0, sizeof(netsnmp_indexed_addr_pair));
            from = &addr_pair->remote_addr.sa;
        }

	while (rc < 0) {
#if defined(linux) && defined(IP_PKTINFO)
            socklen_t local_addr_len = sizeof(addr_pair->local_addr);
            rc = netsnmp_udp_recvfrom(t->sock, buf, size, from, &fromlen,
                                      (struct sockaddr*)&(addr_pair->local_addr),
                                      &local_addr_len, &(addr_pair->if_index));
#else
            rc = recvfrom(t->sock, buf, size, NETSNMP_DONTWAIT, from, &fromlen);
#endif
	    if (rc < 0 && errno != EINTR) {
		break;
	    }
	}

        if (rc >= 0) {
            char *str = netsnmp_udp_fmtaddr(NULL, addr_pair, sizeof(netsnmp_indexed_addr_pair));
            DEBUGMSGTL(("netsnmp_udp",
			"recvfrom fd %d got %d bytes (from %s)\n",
			t->sock, rc, str));
            free(str);
        } else {
            DEBUGMSGTL(("netsnmp_udp", "recvfrom fd %d err %d (\"%s\")\n",
                        t->sock, errno, strerror(errno)));
        }
        *opaque = (void *)addr_pair;
        *olength = sizeof(netsnmp_indexed_addr_pair);
    }
    return rc;
}
