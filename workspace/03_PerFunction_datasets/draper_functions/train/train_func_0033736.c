demand_conf()
{
    int i;
    struct protent *protp;


	framemax = PPP_MRU;
    framemax += PPP_HDRLEN + PPP_FCSLEN;
    frame = malloc(framemax);
    if (frame == NULL)
	novm("demand frame");
    framelen = 0;
    pend_q = NULL;
    escape_flag = 0;
    flush_flag = 0;
    fcs = PPP_INITFCS;

    netif_set_mtu(0, MIN(lcp_allowoptions[0].mru, PPP_MRU));
    netif_set_qlen(0, netif_qlen);
    if (ppp_send_config(0, PPP_MRU, (u_int32_t) 0, 0, 0) < 0
	|| ppp_recv_config(0, PPP_MRU, (u_int32_t) 0, 0, 0) < 0)
	    fatal("Couldn't set up demand-dialled PPP interface: %m");

#ifdef PPP_FILTER
    set_filters(&pass_filter, &active_filter);
#endif


    for (i = 0; (protp = protocols[i]) != NULL; ++i)
	if (protp->enabled_flag && protp->demand_conf != NULL)
	    if (!((*protp->demand_conf)(0)))
		die(1);
}
