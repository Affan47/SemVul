network_init(void)
{
    struct bootp_t *bp = (struct bootp_t *)trackbuf;
    int pkt_len;

    *LocalDomain = 0;


    printf("Getting cached packet ");
    pkt_len = pxe_get_cached_info(1);
    parse_dhcp(pkt_len);


    *(char *)&DHCPMagic = 1;


    pkt_len = pxe_get_cached_info(2);
    parse_dhcp(pkt_len);


    MAC_len = bp->hardlen > 16 ? 0 : bp->hardlen;
    MAC_type = bp->hardware;
    memcpy(MAC, bp->macaddr, MAC_len);


    pkt_len = pxe_get_cached_info(3);
    parse_dhcp(pkt_len);
    printf("\n");

    make_bootif_string();
    make_sysuuid_string();
    ip_init();
    print_ipappend();


    if ((DHCPMagic & 1) == 0)
        DHCPMagic = 0;

    udp_init();
}
