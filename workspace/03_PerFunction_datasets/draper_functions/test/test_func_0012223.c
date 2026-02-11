parse_capabilities (NMSupplicantInterface *self, GHashTable *props)
{
	NMSupplicantInterfacePrivate *priv = NM_SUPPLICANT_INTERFACE_GET_PRIVATE (self);
	GValue *value;
	gboolean have_active = FALSE, have_ssid = FALSE;

	g_return_if_fail (props != NULL);

	value = g_hash_table_lookup (props, "Scan");
	if (value && G_VALUE_HOLDS (value, G_TYPE_STRV)) {
		const char **vals = g_value_get_boxed (value);
		const char **iter = vals;

		while (iter && *iter && (!have_active || !have_ssid)) {
			if (g_strcmp0 (*iter, "active") == 0)
				have_active = TRUE;
			else if (g_strcmp0 (*iter, "ssid") == 0)
				have_ssid = TRUE;
			iter++;
		}
	}

	value = g_hash_table_lookup (props, "MaxScanSSID");
	if (value && G_VALUE_HOLDS (value, G_TYPE_INT)) {

		if (have_active && have_ssid) {


			priv->max_scan_ssids = CLAMP (g_value_get_int (value), 0, 5);
			nm_log_info (LOGD_SUPPLICANT, "(%s) supports %d scan SSIDs",
			             priv->dev, priv->max_scan_ssids);
		}
	}
}
