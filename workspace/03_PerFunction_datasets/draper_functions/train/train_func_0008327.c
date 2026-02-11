nm_on_signal (GDBusProxy* proxy, gchar* sender, gchar* signal_name, GVariant* parameters, gpointer data)
{
	if (g_strcmp0(signal_name, "StateChanged") == 0)
	{
		makiInstance* inst = maki_instance_get_default();
		guint32 state;
		gboolean is_sleeping = FALSE;

		gboolean (*sleeping) (void);

		if (maki_instance_plugin_method(inst, "sleep", "sleeping", (gpointer*)&sleeping))
		{
			is_sleeping = sleeping();
		}

		if (is_sleeping)
		{
			return;
		}

		g_variant_get(parameters, "(u)", &state);

		switch (state)
		{

			case NM_OLD_STATE_CONNECTED:
			case NM_STATE_UNKNOWN:
			case NM_STATE_CONNECTED_LOCAL:
			case NM_STATE_CONNECTED_SITE:
			case NM_STATE_CONNECTED_GLOBAL:
				if (!is_connected)
				{
					is_connected = TRUE;
					servers_connect();
				}

				break;

			case NM_OLD_STATE_ASLEEP:
			case NM_OLD_STATE_CONNECTING:
			case NM_OLD_STATE_DISCONNECTED:
			case NM_STATE_ASLEEP:
			case NM_STATE_DISCONNECTED:
			case NM_STATE_DISCONNECTING:
			case NM_STATE_CONNECTING:
				if (is_connected)
				{
					is_connected = FALSE;
					servers_disconnect("Network configuration changed.");
				}

				break;

			default:
				g_warn_if_reached();
		}
	}
}
