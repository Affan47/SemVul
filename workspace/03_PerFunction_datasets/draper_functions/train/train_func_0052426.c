netsnmp_udpbase_recvfrom(int s, void *buf, int len, struct sockaddr *from,
                         socklen_t *fromlen, struct sockaddr *dstip,
                         socklen_t *dstlen, int *if_index)
{
    int r;
    struct iovec iov;
    char cmsg[CMSG_SPACE(cmsg_data_size)];
    struct cmsghdr *cm;
    struct msghdr msg;

    iov.iov_base = buf;
    iov.iov_len = len;

    memset(&msg, 0, sizeof msg);
    msg.msg_name = from;
    msg.msg_namelen = *fromlen;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = &cmsg;
    msg.msg_controllen = sizeof(cmsg);

    r = recvmsg(s, &msg, NETSNMP_DONTWAIT);

    if (r == -1) {
        return -1;
    }

    DEBUGMSGTL(("udpbase:recv", "got source addr: %s\n",
                inet_ntoa(((struct sockaddr_in *)from)->sin_addr)));

    {

        int r2 = getsockname(s, dstip, dstlen);
        netsnmp_assert(r2 == 0);
    }

    for (cm = CMSG_FIRSTHDR(&msg); cm != NULL; cm = CMSG_NXTHDR(&msg, cm)) {
#if  defined(linux) && defined(IP_PKTINFO)
        if (cm->cmsg_level == SOL_IP && cm->cmsg_type == IP_PKTINFO) {
            struct in_pktinfo* src = (struct in_pktinfo *)CMSG_DATA(cm);
            netsnmp_assert(dstip->sa_family == AF_INET);
            ((struct sockaddr_in*)dstip)->sin_addr = src->ipi_addr;
            *if_index = src->ipi_ifindex;
            DEBUGMSGTL(("udpbase:recv",
                        "got destination (local) addr %s, iface %d\n",
                        inet_ntoa(((struct sockaddr_in*)dstip)->sin_addr),
                        *if_index));
        }
#elif defined(IP_RECVDSTADDR)
        if (cm->cmsg_level == IPPROTO_IP && cm->cmsg_type == IP_RECVDSTADDR) {
            struct in_addr* src = (struct in_addr *)CMSG_DATA(cm);
            ((struct sockaddr_in*)dstip)->sin_addr = *src;
            DEBUGMSGTL(("netsnmp_udp", "got destination (local) addr %s\n",
                        inet_ntoa(((struct sockaddr_in*)dstip)->sin_addr)));
        }
#endif
    }
    return r;
}
