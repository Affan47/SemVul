lcp_update_echo_timer(struct ppp_lcp_t *lcp)
{
	if (!lcp->echo_timer.expire)
		return;

	if (lcp->echo_timer.period != conf_echo_interval * 1000) {
		if (!conf_echo_interval)
			triton_timer_del(&lcp->echo_timer);
		else {
			lcp->echo_timer.period = conf_echo_interval * 1000;
			if (lcp->echo_timer.tpd)
				triton_timer_mod(&lcp->echo_timer, 0);
			else
				triton_timer_add(lcp->ppp->ses.ctrl->ctx, &lcp->echo_timer, 0);
		}
	}
}
