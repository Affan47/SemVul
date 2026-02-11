ppp_ipcp_finished_notify(GAtPPP *ppp)
{
	if (ppp->phase != PPP_PHASE_NETWORK)
		return;


	ppp->disconnect_reason = G_AT_PPP_REASON_IPCP_FAIL;
	pppcp_signal_close(ppp->ipcp);
	pppcp_signal_close(ppp->lcp);
}
