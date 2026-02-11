get_connection_state_for_message (SoupConnectionAuth *auth, SoupMessage *msg)
{
	SoupConnection *conn;
	gpointer state;

	conn = soup_message_get_connection (msg);
	state = g_hash_table_lookup (auth->priv->conns, conn);
	if (state)
		return state;

	state = SOUP_CONNECTION_AUTH_GET_CLASS (auth)->create_connection_state (auth);
	if (conn) {
		g_signal_connect (conn, "disconnected",
				  G_CALLBACK (connection_disconnected), auth);
	}

	g_hash_table_insert (auth->priv->conns, conn, state);
	return state;
}
