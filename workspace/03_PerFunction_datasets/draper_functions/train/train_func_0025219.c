recv_packet(int sockfd, int &ifn, unsigned char macaddr[], unsigned char *data, int maxlen, bool &more)
{
    struct msghdr msg;
    struct iovec iov;
    struct sockaddr_ll sock_info;
    int    len;


    more = false;

    memset(&msg, 0, sizeof(msg));
    msg.msg_name = &sock_info;
    msg.msg_namelen = sizeof(sock_info);
    msg.msg_iovlen = 1;
    msg.msg_iov = &iov;
    iov.iov_len = maxlen;
    iov.iov_base = data;

    len = recvmsg(sockfd, &msg, 0);

    ifn = sock_info.sll_ifindex;
    memcpy(macaddr, sock_info.sll_addr, 6);


    if (sock_info.sll_pkttype == PACKET_OTHERHOST)
    {
	debuglog(("Got a rogue packet .. interface probably in promiscuous mode\n"));
	return 0;
    }
    return len;
}
