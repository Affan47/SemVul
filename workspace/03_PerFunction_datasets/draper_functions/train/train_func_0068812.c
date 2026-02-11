ipoe_relay_timeout(struct triton_timer_t *t)
{
	struct ipoe_session *ses = container_of(t, typeof(*ses), timer);

	if (!ses->serv->dhcpv4_relay || !ses->dhcpv4_request) {
		triton_timer_del(t);
		return;
	}

	if (++ses->relay_retransmit > conf_relay_retransmit) {
		triton_timer_del(t);

		log_ppp_info2("ipoe: relay timed out\n");

		ap_session_terminate(&ses->ses, TERM_LOST_CARRIER, 0);
	} else
		dhcpv4_relay_send(ses->serv->dhcpv4_relay, ses->dhcpv4_request, ses->relay_server_id, ses->serv->ifname, conf_agent_remote_id);
}
