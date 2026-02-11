debugger_server_send_line (DebuggerServer *object, const gchar* line)
{
	DebuggerServerPrivate *priv = DEBUGGER_SERVER_PRIVATE (object);
	g_assert (line != NULL);
	priv->out = g_list_append (priv->out, g_strdup (line));
}
