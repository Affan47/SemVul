nm_on_signal (GDBusProxy* proxy, gchar* sender, gchar* signal_name, GVariant* parameters, gpointer data)
{
	if (g_strcmp0(signal_name, "StateChanged") == 0)
	{
		guint32 state;

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
				servers_connect();
				break;
			default:
				;
		}
	}
}
