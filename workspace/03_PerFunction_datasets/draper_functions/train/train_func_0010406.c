dispose (GObject *object)
{
	SCPluginOfono *plugin = SC_PLUGIN_OFONO (object);
	SCPluginOfonoPrivate *priv = SC_PLUGIN_OFONO_GET_PRIVATE (plugin);

	if (priv->bus) {
		dbus_g_connection_unref (priv->bus);
		priv->bus = NULL;
	}

	if (priv->ofono_dir_monitor) {
		if (priv->ofono_dir_monitor_id)
			g_signal_handler_disconnect (priv->ofono_dir_monitor,
			                             priv->ofono_dir_monitor_id);

		g_file_monitor_cancel (priv->ofono_dir_monitor);
		g_object_unref (priv->ofono_dir_monitor);
		priv->ofono_dir_monitor = NULL;
	}

	if (priv->ofono_imsi_monitors) {
		g_hash_table_foreach (priv->ofono_imsi_monitors, cancel_monitor, priv->ofono_imsi_monitor_ids);

		g_hash_table_destroy (priv->ofono_imsi_monitors);
		priv->ofono_imsi_monitors = NULL;

		if (priv->ofono_imsi_monitor_ids) {
			g_hash_table_destroy (priv->ofono_imsi_monitor_ids);
			priv->ofono_imsi_monitor_ids = NULL;
		}
	}

	if (priv->connections) {
		g_hash_table_destroy (priv->connections);
		priv->connections = NULL;
	}

	G_OBJECT_CLASS (sc_plugin_ofono_parent_class)->dispose (object);
}
