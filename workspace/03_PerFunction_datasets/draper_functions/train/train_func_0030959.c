io_disconnect(gpointer user_data)
{
	GAtPPP *ppp = user_data;

	if (ppp->phase == PPP_PHASE_DEAD)
		return;

	ppp->disconnect_reason = G_AT_PPP_REASON_LINK_DEAD;
	pppcp_signal_down(ppp->lcp);
	pppcp_signal_close(ppp->lcp);
}
