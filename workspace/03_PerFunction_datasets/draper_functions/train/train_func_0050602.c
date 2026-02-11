server_cleanup(XMPP_SERVER_REC *server)
{
	if (!IS_XMPP_SERVER(server))
		return;
	if (server->timeout_tag)
		g_source_remove(server->timeout_tag);
	if (lm_connection_get_state(server->lmconn) !=
	    LM_CONNECTION_STATE_CLOSED)
		lm_connection_close(server->lmconn, NULL);
	lm_connection_unref(server->lmconn);
	g_free(server->jid);
	g_free(server->user);
	g_free(server->domain);
	g_free(server->resource);
	g_free(server->ping_id);
}
