lcp_lowerup(unit)
    int unit;
{
    lcp_options *wo = &lcp_wantoptions[unit];
    fsm *f = &lcp_fsm[unit];


    if (ppp_send_config(unit, PPP_MRU, 0xffffffff, 0, 0) < 0
	|| ppp_recv_config(unit, PPP_MRU, (lax_recv? 0: 0xffffffff),
			   wo->neg_pcompression, wo->neg_accompression) < 0)
	    return;
    peer_mru[unit] = PPP_MRU;

    if (listen_time != 0) {
	f->flags |= DELAYED_UP;
	timeout(lcp_delayed_up, f, 0, listen_time * 1000);
    } else
	fsm_lowerup(f);
}
