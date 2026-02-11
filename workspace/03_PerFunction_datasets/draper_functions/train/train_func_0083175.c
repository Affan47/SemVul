ancillary_s_ip_pktinfo(int argc, VALUE *argv, VALUE self)
{
    VALUE v_addr, v_ifindex, v_spec_dst;
    unsigned int ifindex;
    struct sockaddr_in sa;
    struct in_pktinfo pktinfo;

    rb_scan_args(argc, argv, "21", &v_addr, &v_ifindex, &v_spec_dst);

    SockAddrStringValue(v_addr);
    ifindex = NUM2UINT(v_ifindex);
    if (NIL_P(v_spec_dst))
        v_spec_dst = v_addr;
    else
        SockAddrStringValue(v_spec_dst);

    memset(&pktinfo, 0, sizeof(pktinfo));

    memset(&sa, 0, sizeof(sa));
    if (RSTRING_LEN(v_addr) != sizeof(sa))
        rb_raise(rb_eArgError, "addr size different to AF_INET sockaddr");
    memcpy(&sa, RSTRING_PTR(v_addr), sizeof(sa));
    if (sa.sin_family != AF_INET)
        rb_raise(rb_eArgError, "addr is not AF_INET sockaddr");
    memcpy(&pktinfo.ipi_addr, &sa.sin_addr, sizeof(pktinfo.ipi_addr));

    pktinfo.ipi_ifindex = ifindex;

    memset(&sa, 0, sizeof(sa));
    if (RSTRING_LEN(v_spec_dst) != sizeof(sa))
        rb_raise(rb_eArgError, "spec_dat size different to AF_INET sockaddr");
    memcpy(&sa, RSTRING_PTR(v_spec_dst), sizeof(sa));
    if (sa.sin_family != AF_INET)
        rb_raise(rb_eArgError, "spec_dst is not AF_INET sockaddr");
    memcpy(&pktinfo.ipi_spec_dst, &sa.sin_addr, sizeof(pktinfo.ipi_spec_dst));

    return ancdata_new(AF_INET, IPPROTO_IP, IP_PKTINFO, rb_str_new((char *)&pktinfo, sizeof(pktinfo)));
}
