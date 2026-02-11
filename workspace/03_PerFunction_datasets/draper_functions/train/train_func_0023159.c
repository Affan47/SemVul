stream_state_changed(struct avdtp_stream *stream,
					avdtp_state_t old_state,
					avdtp_state_t new_state,
					struct avdtp_error *err,
					void *user_data)
{
	struct audio_device *dev = user_data;
	struct sink *sink = dev->sink;
	gboolean value;

	if (err)
		return;

	switch (new_state) {
	case AVDTP_STATE_IDLE:
		if (sink->disconnect) {
			DBusMessage *reply;
			struct pending_request *p;

			p = sink->disconnect;
			sink->disconnect = NULL;

			reply = dbus_message_new_method_return(p->msg);
			g_dbus_send_message(p->conn, reply);
			pending_request_free(dev, p);
		}

		if (sink->session) {
			avdtp_unref(sink->session);
			sink->session = NULL;
		}
		sink->stream = NULL;
		sink->cb_id = 0;
		break;
	case AVDTP_STATE_OPEN:
		if (old_state == AVDTP_STATE_CONFIGURED &&
				sink->state == SINK_STATE_CONNECTING) {
			value = TRUE;
			g_dbus_emit_signal(dev->conn, dev->path,
						AUDIO_SINK_INTERFACE,
						"Connected",
						DBUS_TYPE_INVALID);
			emit_property_changed(dev->conn, dev->path,
						AUDIO_SINK_INTERFACE,
						"Connected",
						DBUS_TYPE_BOOLEAN, &value);
		} else if (old_state == AVDTP_STATE_STREAMING) {
			value = FALSE;
			g_dbus_emit_signal(dev->conn, dev->path,
						AUDIO_SINK_INTERFACE,
						"Stopped",
						DBUS_TYPE_INVALID);
			emit_property_changed(dev->conn, dev->path,
						AUDIO_SINK_INTERFACE,
						"Playing",
						DBUS_TYPE_BOOLEAN, &value);
		}
		sink_set_state(dev, SINK_STATE_CONNECTED);
		break;
	case AVDTP_STATE_STREAMING:
		value = TRUE;
		g_dbus_emit_signal(dev->conn, dev->path, AUDIO_SINK_INTERFACE,
					"Playing", DBUS_TYPE_INVALID);
		emit_property_changed(dev->conn, dev->path,
					AUDIO_SINK_INTERFACE, "Playing",
					DBUS_TYPE_BOOLEAN, &value);
		sink_set_state(dev, SINK_STATE_PLAYING);
		break;
	case AVDTP_STATE_CONFIGURED:
	case AVDTP_STATE_CLOSING:
	case AVDTP_STATE_ABORTING:
	default:
		break;
	}

	sink->stream_state = new_state;
}
