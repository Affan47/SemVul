udp_set_url(struct sockaddr_storage *addr, const char *hostname, int port) {
    struct addrinfo *res0;
    int addr_len;

    res0 = udp_ipv6_resolve_host(hostname, port, SOCK_DGRAM, AF_UNSPEC, 0);
    if (res0 == 0) return AVERROR(EIO);
    memcpy(addr, res0->ai_addr, res0->ai_addrlen);
    addr_len = res0->ai_addrlen;
    freeaddrinfo(res0);

    return addr_len;
}
