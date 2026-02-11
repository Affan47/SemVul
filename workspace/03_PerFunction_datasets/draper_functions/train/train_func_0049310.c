nm_vpn_manager_deactivate_connection (NMVPNManager *self,
                                      NMVPNConnection *connection,
                                      NMVPNConnectionStateReason reason)
{
	NMVPNManagerPrivate *priv;
	GHashTableIter iter;
	gpointer data;
	const GSList *active, *aiter;
	gboolean success = FALSE;

	g_return_val_if_fail (self, FALSE);
	g_return_val_if_fail (NM_IS_VPN_MANAGER (self), FALSE);
	g_return_val_if_fail (connection != NULL, FALSE);

	priv = NM_VPN_MANAGER_GET_PRIVATE (self);
	g_hash_table_iter_init (&iter, priv->services);
	while (g_hash_table_iter_next (&iter, NULL, &data) && (success == FALSE)) {
		active = nm_vpn_service_get_active_connections (NM_VPN_SERVICE (data));
		for (aiter = active; aiter; aiter = g_slist_next (aiter)) {
			NMVPNConnection *candidate = aiter->data;

			if (connection == candidate) {
				nm_vpn_connection_disconnect (connection, reason);
				success = TRUE;
				break;
			}
		}
	}

	return success;
}
