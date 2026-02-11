wlan_proxy_created (GObject *source_object,
                    GAsyncResult *res,
                    gpointer user_data)
{
	NMUrfkillManager *self;
	GDBusProxy *wlan_proxy;
	GError *error;

	wlan_proxy = g_dbus_proxy_new_for_bus_finish (res, &error);

	if (!error || error->code != G_IO_ERROR_CANCELLED)
 		self = NM_URFKILL_MANAGER (user_data);

	if (wlan_proxy) {
		self->wlan_proxy = wlan_proxy;

		g_signal_connect (self->wlan_proxy, "g-properties-changed",
		                  G_CALLBACK (wlan_state_changed), self);
		g_signal_emit (self, signals[WLAN_STATE_CHANGED], 0,
		               nm_urfkill_get_wlan_state (self));
	} else {
		nm_log_warn (LOGD_RFKILL, "could not create URfkill WLAN device proxy");
	}
}
