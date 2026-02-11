gf_rtp_get_ports(GF_RTPChannel *ch, u16 *rtp_port, u16 *rtcp_port)
{
	if (ch->net_info.client_port_first) {
		if (rtp_port) *rtp_port = ch->net_info.client_port_first;
		if (rtcp_port) *rtcp_port = ch->net_info.client_port_last;
	} else {
		if (rtp_port) *rtp_port = ch->net_info.port_first;
		if (rtcp_port) *rtcp_port = ch->net_info.port_last;
	}
}
