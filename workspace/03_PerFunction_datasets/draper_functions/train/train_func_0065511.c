netsnmp_udpbase_recvfrom(int s, void *buf, int len, struct sockaddr *from,
                         socklen_t *fromlen, struct sockaddr *dstip,
                         socklen_t *dstlen, int *if_index)
{
    int r, r2;
    struct iovec iov[1];
#if  defined(linux) && defined(IP_PKTINFO)
    char cmsg[CMSG_SPACE(sizeof(struct in_pktinfo))];
#elif defined(IP_RECVDSTADDR)
    char cmsg[CMSG_SPACE(sizeof(struct in_addr))];
#endif
    struct cmsghdr *cmsgptr;
    struct msghdr msg;

    iov[0].iov_base = buf;
    iov[0].iov_len = len;

    memset(&msg, 0, sizeof msg);
    msg.msg_name = from;
    msg.msg_namelen = *fromlen;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_control = &cmsg;
    msg.msg_controllen = sizeof(cmsg);

    r = recvmsg(s, &msg, NETSNMP_DONTWAIT);

    if (r == -1) {
        return -1;
    }

    r2 = getsockname(s, dstip, dstlen);
    netsnmp_assert(r2 == 0);

    DEBUGMSGTL(("udpbase:recv", "got source addr: %s\n",
                inet_ntoa(((struct sockaddr_in *)from)->sin_addr)));
#if  defined(linux) && defined(IP_PKTINFO)
    for (cmsgptr = CMSG_FIRSTHDR(&msg); cmsgptr != NULL; cmsgptr = CMSG_NXTHDR(&msg, cmsgptr)) {
        if (cmsgptr->cmsg_level != SOL_IP || cmsgptr->cmsg_type != IP_PKTINFO)
            continue;

        netsnmp_assert(dstip->sa_family == AF_INET);
        ((struct sockaddr_in*)dstip)->sin_addr = *netsnmp_dstaddr(cmsgptr);
        *if_index = (((struct in_pktinfo *)(CMSG_DATA(cmsgptr)))->ipi_ifindex);
        DEBUGMSGTL(("udpbase:recv",
                    "got destination (local) addr %s, iface %d\n",
                    inet_ntoa(((struct sockaddr_in*)dstip)->sin_addr),
                    *if_index));
    }
#elif defined(IP_RECVDSTADDR)
    for (cmsgptr = CMSG_FIRSTHDR(&msg); cmsgptr != NULL; cmsgptr = CMSG_NXTHDR(&msg, cmsgptr)) {
        if (cmsgptr->cmsg_level == IPPROTO_IP && cmsgptr->cmsg_type == IP_RECVDSTADDR) {
            memcpy((void *) dstip, CMSG_DATA(cmsgptr), sizeof(struct in_addr));
            DEBUGMSGTL(("netsnmp_udp", "got destination (local) addr %s\n",
                    inet_ntoa(((struct sockaddr_in*)dstip)->sin_addr)));
        }
    }
#endif
    return r;
}
