bluetooth_agent_setup(BluetoothAgent *agent, const char *path)
{
	BluetoothAgentPrivate *priv = BLUETOOTH_AGENT_GET_PRIVATE(agent);
	GError *error = NULL;

	if (priv->path != NULL) {
		g_warning ("Agent already setup on '%s'", priv->path);
		return FALSE;
	}

	priv->path = g_strdup(path);

	priv->reg_id = g_dbus_connection_register_object (priv->conn,
						      priv->path,
						      priv->introspection_data->interfaces[0],
						      &interface_vtable,
						      agent,
						      NULL,
						      &error);
	if (priv->reg_id == 0) {
		g_warning ("Failed to register object: %s", error->message);
		g_error_free (error);
	}

	return TRUE;
}
