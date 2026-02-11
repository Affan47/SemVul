gfire_p2p_session_send_keep_alive(gfire_p2p_session *p_session)
{
	if(!p_session || !p_session->con)
		return;

	p_session->need_keep_alive = TRUE;
	GTimeVal gtv;
	g_get_current_time(&gtv);
	p_session->last_keep_alive = gtv.tv_sec;

	gfire_p2p_connection_send_keep_alive(p_session->con, p_session->moniker_self, p_session->sessid,
										 gfire_p2p_session_get_peer_addr(p_session, GF_P2P_ADDR_TYPE_USE));
}
