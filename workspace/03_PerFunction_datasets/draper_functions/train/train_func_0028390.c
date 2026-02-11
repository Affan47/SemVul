pk_client_helper_finalize (GObject *object)
{
	PkClientHelper *client_helper = PK_CLIENT_HELPER (object);
	PkClientHelperPrivate *priv = client_helper->priv;

	if (priv->socket_file != NULL)
		g_object_unref (priv->socket_file);
	if (priv->io_channel_socket != NULL)
		g_io_channel_unref (priv->io_channel_socket);
	if (priv->io_channel_temp != NULL)
		g_io_channel_unref (priv->io_channel_temp);
	if (priv->io_channel_child_stdin != NULL)
		g_io_channel_unref (priv->io_channel_child_stdin);
	if (priv->io_channel_child_stdout != NULL)
		g_io_channel_unref (priv->io_channel_child_stdout);
	if (priv->io_channel_child_stderr != NULL)
		g_io_channel_unref (priv->io_channel_child_stderr);
	g_strfreev (priv->argv);
	g_strfreev (priv->envp);

	G_OBJECT_CLASS (pk_client_helper_parent_class)->finalize (object);
}
