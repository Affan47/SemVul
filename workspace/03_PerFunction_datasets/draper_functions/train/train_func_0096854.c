bluetooth_agent_register(BluetoothAgent *agent)
{
	BluetoothAgentPrivate *priv;
	GError *error = NULL;
	char *path;
	GVariant *r;

	g_return_val_if_fail (BLUETOOTH_IS_AGENT (agent), FALSE);

	priv = BLUETOOTH_AGENT_GET_PRIVATE (agent);

	priv->adapter = get_default_adapter ();

	if (priv->adapter == NULL)
		return FALSE;

	if (priv->path != NULL) {
		g_warning ("Agent already setup on '%s'", priv->path);
		return FALSE;
	}

	path = g_path_get_basename(g_dbus_proxy_get_object_path(priv->adapter));
	priv->path = g_strdup_printf("/org/bluez/agent/%s", path);
	g_free(path);

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
		error = NULL;
		return FALSE;
	}

	r = g_dbus_proxy_call_sync (priv->adapter, "RegisterAgent",
				    g_variant_new ("(os)", priv->path, "DisplayYesNo"),
				    G_DBUS_CALL_FLAGS_NONE,
				    -1, NULL, &error);
	if (r == NULL) {
		g_printerr ("Agent registration failed: %s\n", error->message);
		g_error_free (error);
		return FALSE;
	}
	g_variant_unref (r);

	return TRUE;
}
