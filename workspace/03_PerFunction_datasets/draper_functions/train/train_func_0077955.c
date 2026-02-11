request_add_agents (NMAgentManager *self, Request *req)
{
	NMAgentManagerPrivate *priv = NM_AGENT_MANAGER_GET_PRIVATE (self);
	GHashTableIter iter;
	gpointer data;

	g_hash_table_iter_init (&iter, priv->agents);
	while (g_hash_table_iter_next (&iter, NULL, &data))
		request_add_agent (req, NM_SECRET_AGENT (data), priv->session_monitor);
}
