anc_inspect_ipv6_pktinfo(int level, int type, VALUE data, VALUE ret)
{
    if (level == IPPROTO_IPV6 && type == IPV6_PKTINFO &&
        RSTRING_LEN(data) == sizeof(struct in6_pktinfo)) {
        struct in6_pktinfo *pktinfo = (struct in6_pktinfo *)RSTRING_PTR(data);
        struct in6_addr addr;
        unsigned int ifindex;
        char addrbuf[INET6_ADDRSTRLEN], ifbuf[IFNAMSIZ];
        memcpy(&addr, &pktinfo->ipi6_addr, sizeof(addr));
        memcpy(&ifindex, &pktinfo->ipi6_ifindex, sizeof(ifindex));
        if (inet_ntop(AF_INET6, &addr, addrbuf, (socklen_t)sizeof(addrbuf)) == NULL)
            rb_str_cat2(ret, " invalid-address");
        else
            rb_str_catf(ret, " %s", addrbuf);
        if (if_indextoname(ifindex, ifbuf) == NULL)
            rb_str_catf(ret, " ifindex:%d", ifindex);
        else
            rb_str_catf(ret, " %s", ifbuf);
        return 1;
    }
    else {
        return 0;
    }
}
