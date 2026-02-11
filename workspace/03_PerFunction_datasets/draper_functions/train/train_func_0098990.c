gfire_p2p_packet_resend_send(gfire_p2p_packet_resend *p_packet, gfire_p2p_connection *p_p2p,
										 guint8 p_encoding)
{
	if(!p_packet || !p_p2p)
		return;

	guint32 offset = 0;
	switch(p_packet->type)
	{
	case GFIRE_P2P_TYPE_DATA16:
	case GFIRE_P2P_TYPE_DATA32:
		offset = gfire_p2p_connection_write_header(p_p2p, p_encoding, p_packet->moniker, p_packet->type,
												   p_packet->msgid, p_packet->seqid, p_packet->data_len);
		if(offset == 0)
			return;

		offset = gfire_p2p_connection_write_data(p_p2p, p_encoding, p_packet->data, p_packet->data_len,
											 p_packet->category, offset);
		if(offset == 0)
			return;

		gfire_p2p_connection_send(p_p2p, gfire_p2p_session_get_peer_addr(p_packet->session, GF_P2P_ADDR_TYPE_USE),
								  offset);
		break;
	default:
		purple_debug_warning("gfire", "P2P: gfire_p2p_packet_resend_send: unknown packet type!");
	}

	p_packet->retries++;
}
