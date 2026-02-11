mp_check_options()
{
	lcp_options *wo = &lcp_wantoptions[0];
	lcp_options *ao = &lcp_allowoptions[0];
        FUNC_DEBUG("%s: %d\n", __FUNCTION__,__LINE__);
	doing_multilink = 0;
	if (!multilink)
		return;

	if (!wo->neg_mrru) {

		wo->mrru = wo->mru;
		wo->neg_mrru = 1;
	}
	ao->mrru = ao->mru;
	ao->neg_mrru = 1;

	if (!wo->neg_endpoint && !noendpoint) {

		wo->neg_endpoint = get_default_epdisc(&wo->endpoint);
	}
}
