stage1_prepare_done (DBusGProxy *proxy, DBusGProxyCall *call, gpointer user_data)
{
	NMModemOfono *self = NM_MODEM_OFONO (user_data);
	NMModemOfonoPrivate *priv = NM_MODEM_OFONO_GET_PRIVATE (self);
	GError *error = NULL;

	nm_log_dbg (LOGD_MB, "in %s", __func__);

	priv->call = NULL;

	if (priv->connect_properties) {
		g_hash_table_destroy (priv->connect_properties);
		priv->connect_properties = NULL;
	}

	if (!dbus_g_proxy_end_call (proxy, call, &error, G_TYPE_INVALID)) {
		nm_log_warn (LOGD_MB, "OFONO connection failed: (%d) %s",
		             error ? error->code : -1,
		             error && error->message ? error->message : "(unknown)");

		g_signal_emit_by_name (self, NM_MODEM_PREPARE_RESULT, FALSE, translate_mm_error (error));

		g_error_free (error);
	}
}
