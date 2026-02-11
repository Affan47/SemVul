pppoe_check_options(void)
{
    unsigned int mac[6];
    int i;

    if (pppoe_reqd_mac != NULL) {
	if (sscanf(pppoe_reqd_mac, "%x:%x:%x:%x:%x:%x",
		   &mac[0], &mac[1], &mac[2], &mac[3],
		   &mac[4], &mac[5]) != 6) {
	    option_error("cannot parse pppoe-mac option value");
	    exit(EXIT_OPTION_ERROR);
	}
	for (i = 0; i < 6; ++i)
	    conn->req_peer_mac[i] = mac[i];
	conn->req_peer = 1;
    }

    lcp_allowoptions[0].neg_accompression = 0;
    lcp_wantoptions[0].neg_accompression = 0;

    lcp_allowoptions[0].neg_asyncmap = 0;
    lcp_wantoptions[0].neg_asyncmap = 0;

    lcp_allowoptions[0].neg_pcompression = 0;
    lcp_wantoptions[0].neg_pcompression = 0;

    if (lcp_allowoptions[0].mru > MAX_PPPOE_MTU)
	lcp_allowoptions[0].mru = MAX_PPPOE_MTU;
    if (lcp_wantoptions[0].mru > MAX_PPPOE_MTU)
	lcp_wantoptions[0].mru = MAX_PPPOE_MTU;


    conn->mtu = lcp_allowoptions[0].mru;
    conn->mru = lcp_wantoptions[0].mru;

    ccp_allowoptions[0].deflate = 0;
    ccp_wantoptions[0].deflate = 0;

    ipcp_allowoptions[0].neg_vj = 0;
    ipcp_wantoptions[0].neg_vj = 0;

    ccp_allowoptions[0].bsd_compress = 0;
    ccp_wantoptions[0].bsd_compress = 0;
}
