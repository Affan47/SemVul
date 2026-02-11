connection_state_changed (GObject *object, GParamSpec *param, gpointer user_data)
{
	SoupSession *session = user_data;
	SoupConnection *conn = SOUP_CONNECTION (object);

	if (soup_connection_get_state (conn) == SOUP_CONNECTION_IDLE)
		soup_session_kick_queue (session);
}
