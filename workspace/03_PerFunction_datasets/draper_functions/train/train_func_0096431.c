gfire_p2p_connection_remove_session(gfire_p2p_connection *p_p2p, gfire_p2p_session *p_session)
{
	if(!p_p2p || !p_p2p->sessions || !p_session)
		return;

	GList *session = g_list_find(p_p2p->sessions, p_session);
	if(!session)
		return;


	GList *cur_packet = p_p2p->packets;
	while(cur_packet)
	{
		gfire_p2p_packet_resend *packet = cur_packet->data;
		if(packet->session == p_session)
		{
			gfire_p2p_packet_resend_free(packet);
			p_p2p->packets = g_list_delete_link(p_p2p->packets, cur_packet);
			cur_packet = p_p2p->packets;
			continue;
		}

		cur_packet = g_list_next(cur_packet);
	}

	p_p2p->sessions = g_list_delete_link(p_p2p->sessions, session);

	purple_debug_info("gfire", "P2P: Session removed (%u left)\n", g_list_length(p_p2p->sessions));
}
