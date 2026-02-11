check_network(struct network *net)
{
    int ifindex, rc;
    struct ipv6_mreq mreq;

    ifindex = if_nametoindex(net->ifname);
    if(ifindex != net->ifindex) {
        net->ifindex = ifindex;
        if(net->ifindex > 0) {
            memset(&mreq, 0, sizeof(mreq));
            memcpy(&mreq.ipv6mr_multiaddr, &protocol_group, 16);
            mreq.ipv6mr_interface = net->ifindex;
            rc = setsockopt(protocol_socket, IPPROTO_IPV6, IPV6_JOIN_GROUP,
                            (char*)&mreq, sizeof(mreq));
            if(rc < 0) {
                perror("setsockopt(IPV6_JOIN_GROUP)");
                net->ifindex = 0;
                goto fail;
            }
            return 1;
        }
    }
 fail:
    return 0;
}
