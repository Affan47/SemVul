e_dbus_server_hold (EDBusServer *server)
{
	g_return_if_fail (E_IS_DBUS_SERVER (server));

	if (server->priv->inactivity_timeout_id > 0) {
		g_source_remove (server->priv->inactivity_timeout_id);
		server->priv->inactivity_timeout_id = 0;
	}

	server->priv->use_count++;
}
