newconnection_reply(DBusPendingCall *call, void *data)
{
	struct audio_device *dev = data;
	struct gateway *gw = dev->gateway;
	DBusMessage *reply = dbus_pending_call_steal_reply(call);
	DBusError derr;

	if (!dev->gateway->rfcomm) {
		DBG("RFCOMM disconnected from server before agent reply");
		goto done;
	}

	dbus_error_init(&derr);
	if (!dbus_set_error_from_message(&derr, reply)) {
		DBG("Agent reply: file descriptor passed successfully");
		g_io_add_watch(gw->rfcomm, G_IO_ERR | G_IO_HUP | G_IO_NVAL,
					(GIOFunc) rfcomm_disconnect_cb, dev);
		change_state(dev, GATEWAY_STATE_CONNECTED);
		goto done;
	}

	DBG("Agent reply: %s", derr.message);

	dbus_error_free(&derr);
	gateway_close(dev);

done:
	dbus_message_unref(reply);
}
