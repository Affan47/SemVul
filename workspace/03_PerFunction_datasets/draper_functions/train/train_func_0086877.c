connect_cb(struct vpn_provider *provider, void *user_data,
								int error)
{
	DBusMessage *pending = user_data;

	DBG("provider %p user %p error %d", provider, user_data, error);

	if (error != 0) {
		DBusMessage *reply = __connman_error_failed(pending, error);
		if (reply != NULL)
			g_dbus_send_message(connection, reply);

		vpn_provider_indicate_error(provider,
					VPN_PROVIDER_ERROR_CONNECT_FAILED);
		vpn_provider_set_state(provider, VPN_PROVIDER_STATE_FAILURE);
	} else
		g_dbus_send_reply(connection, pending, DBUS_TYPE_INVALID);

	dbus_message_unref(pending);
}
