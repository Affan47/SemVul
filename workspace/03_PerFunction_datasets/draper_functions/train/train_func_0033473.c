debugger_server_stop (DebuggerServer *object)
{
	DebuggerServerPrivate *priv = DEBUGGER_SERVER_PRIVATE (object);
	if (priv)
		priv->work = FALSE;
}
