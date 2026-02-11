cal_client_refresh_sync (EClient *client,
                         GCancellable *cancellable,
                         GError **error)
{
	ECalClient *cal_client;
	GError *local_error = NULL;

	g_return_val_if_fail (E_IS_CAL_CLIENT (client), FALSE);

	cal_client = E_CAL_CLIENT (client);

	e_dbus_calendar_call_refresh_sync (
		cal_client->priv->dbus_proxy, cancellable, &local_error);

	if (local_error != NULL) {
		g_dbus_error_strip_remote_error (local_error);
		g_propagate_error (error, local_error);
		return FALSE;
	}

	return TRUE;
}
