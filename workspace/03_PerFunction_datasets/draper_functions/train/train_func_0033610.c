network_phase(unit)
    int unit;
{
    int i;
    struct protent *protp;
    lcp_options *go = &lcp_gotoptions[unit];


    if ((go->neg_chap || go->neg_upap) && !did_authup) {
	auth_script(_PATH_AUTHUP);
	did_authup = 1;
    }

#ifdef CBCP_SUPPORT


    if (go->neg_cbcp) {
	phase = PHASE_CALLBACK;
	(*cbcp_protent.open)(unit);
	return;
    }
#endif

    phase = PHASE_NETWORK;
#if 0
    if (!demand)
	set_filters(&pass_filter, &active_filter);
#endif
    for (i = 0; (protp = protocols[i]) != NULL; ++i)
        if (protp->protocol < 0xC000 && protp->enabled_flag
	    && protp->open != NULL) {
	    (*protp->open)(unit);
	    if (protp->protocol != PPP_CCP)
		++num_np_open;
	}

    if (num_np_open == 0)

	lcp_close(0, "No network protocols running");
}
