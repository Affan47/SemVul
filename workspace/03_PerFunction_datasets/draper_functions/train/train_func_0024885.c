ipoe_session_keepalive(struct dhcpv4_packet *pack)
{
	struct ipoe_session *ses = container_of(triton_context_self(), typeof(*ses), ctx);

	if (ses->dhcpv4_request)
		dhcpv4_packet_free(ses->dhcpv4_request);

	ses->dhcpv4_request = pack;

	if (ses->timer.tpd)
		triton_timer_mod(&ses->timer, 0);

	ses->xid = ses->dhcpv4_request->hdr->xid;

	if ( ses->serv->dhcpv4_relay) {
		dhcpv4_relay_send(ses->serv->dhcpv4_relay, ses->dhcpv4_request, ses->relay_server_id, ses->serv->ifname, conf_agent_remote_id);
		return;
	}

	if (ses->ses.state == AP_STATE_ACTIVE) {
		dhcpv4_send_reply(DHCPACK, ses->serv->dhcpv4, ses->dhcpv4_request, ses->yiaddr, ses->siaddr, ses->router, ses->mask, ses->lease_time, ses->dhcpv4_relay_reply);
	} else
		dhcpv4_send_nak(ses->serv->dhcpv4, ses->dhcpv4_request);

	dhcpv4_packet_free(ses->dhcpv4_request);
	ses->dhcpv4_request = NULL;
}
