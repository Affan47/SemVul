state_changed(struct audio_device *dev, avctp_state_t old_state,
				avctp_state_t new_state, void *user_data)
{
	struct control *control = dev->control;
	gboolean value;

	switch (new_state) {
	case AVCTP_STATE_DISCONNECTED:
		control->session = NULL;

		if (old_state != AVCTP_STATE_CONNECTED)
			break;

		value = FALSE;
		g_dbus_emit_signal(dev->conn, dev->path,
					AUDIO_CONTROL_INTERFACE,
					"Disconnected", DBUS_TYPE_INVALID);
		emit_property_changed(dev->conn, dev->path,
					AUDIO_CONTROL_INTERFACE, "Connected",
					DBUS_TYPE_BOOLEAN, &value);

		break;
	case AVCTP_STATE_CONNECTING:
		if (control->session)
			break;

		control->session = avctp_get(&dev->src, &dev->dst);

		break;
	case AVCTP_STATE_CONNECTED:
		value = TRUE;
		g_dbus_emit_signal(dev->conn, dev->path,
				AUDIO_CONTROL_INTERFACE, "Connected",
				DBUS_TYPE_INVALID);
		emit_property_changed(dev->conn, dev->path,
				AUDIO_CONTROL_INTERFACE, "Connected",
				DBUS_TYPE_BOOLEAN, &value);
		break;
	default:
		return;
	}
}
