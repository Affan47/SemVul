agent_display_passkey(struct agent *agent, struct btd_device *device,
				uint32_t passkey, uint16_t entered)
{
	DBusMessage *message;
	const gchar *dev_path = device_get_path(device);

	message = dbus_message_new_method_call(agent->name, agent->path,
				"org.bluez.Agent", "DisplayPasskey");
	if (!message) {
		error("Couldn't allocate D-Bus message");
		return -1;
	}

	DBG("agent_display_passkey: %d,%d",passkey,entered);

	dbus_message_append_args(message,
				DBUS_TYPE_OBJECT_PATH, &dev_path,
				DBUS_TYPE_UINT32, &passkey,
				DBUS_TYPE_UINT16, &entered,
				DBUS_TYPE_INVALID);

	if (!g_dbus_send_message(connection, message)) {
		error("D-Bus send failed");
		return -1;
	}

	return 0;
}
