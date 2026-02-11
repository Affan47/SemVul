plugin_need_secrets_cb  (DBusGProxy *proxy,
                         char *setting_name,
                         GError *error,
                         gpointer user_data)
{
	NMVPNConnection *self = NM_VPN_CONNECTION (user_data);
	NMVPNConnectionPrivate *priv = NM_VPN_CONNECTION_GET_PRIVATE (self);

	if (error) {
		nm_log_err (LOGD_VPN, "(%s/%s) plugin NeedSecrets request #%d failed: %s %s",
		            nm_connection_get_uuid (priv->connection),
		            nm_connection_get_id (priv->connection),
		            priv->secrets_idx + 1,
		            g_quark_to_string (error->domain),
		            error->message);
		nm_vpn_connection_fail (self, NM_VPN_CONNECTION_STATE_REASON_NO_SECRETS);
		return;
	}

	if (setting_name && strlen (setting_name)) {


		if (priv->secrets_idx == SECRETS_REQ_NEW) {
			nm_log_err (LOGD_VPN, "(%s/%s) final secrets request failed to provide sufficient secrets",
			            nm_connection_get_uuid (priv->connection),
			            nm_connection_get_id (priv->connection));
			nm_vpn_connection_fail (self, NM_VPN_CONNECTION_STATE_REASON_NO_SECRETS);
		} else {
			nm_log_dbg (LOGD_VPN, "(%s/%s) service indicated additional secrets required",
			            nm_connection_get_uuid (priv->connection),
			            nm_connection_get_id (priv->connection));

			get_secrets (self, priv->secrets_idx + 1);
		}
		return;
	}

	nm_log_dbg (LOGD_VPN, "(%s/%s) service indicated no additional secrets required",
	            nm_connection_get_uuid (priv->connection),
	            nm_connection_get_id (priv->connection));


	really_activate (self, priv->username);
}
