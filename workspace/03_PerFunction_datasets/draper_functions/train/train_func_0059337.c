netreg_property_changed_cb (DBusGProxy *proxy,
                            char *name,
                            GValue *value,
                            Modem *modem)
{
	char *str;

	if (g_strcmp0 ("LocationAreaCode", name) == 0) {
		str = g_strdup_printf ("%u", g_value_get_uint (value));
		if (modem_set_lac (modem, str)) {
			emit_network_data_changed (modem->ofono);
		}
		g_free (str);
	} else if (g_strcmp0 ("CellId", name) == 0) {
		str = g_strdup_printf ("%u", g_value_get_uint (value));
		if (modem_set_cid (modem, str)) {
			emit_network_data_changed (modem->ofono);
		}
		g_free (str);
	} else if (g_strcmp0 ("AvailableOperators", name) == 0) {
		modem_set_net_ops (modem, g_value_get_boxed (value));
	}
}
