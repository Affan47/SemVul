avctp_confirm_cb(GIOChannel *chan, gpointer data)
{
	struct avctp *session;
	struct audio_device *dev;
	char address[18];
	bdaddr_t src, dst;
	GError *err = NULL;

	bt_io_get(chan, BT_IO_L2CAP, &err,
			BT_IO_OPT_SOURCE_BDADDR, &src,
			BT_IO_OPT_DEST_BDADDR, &dst,
			BT_IO_OPT_DEST, address,
			BT_IO_OPT_INVALID);
	if (err) {
		error("%s", err->message);
		g_error_free(err);
		g_io_channel_shutdown(chan, TRUE, NULL);
		return;
	}

	DBG("AVCTP: incoming connect from %s", address);

	session = avctp_get_internal(&src, &dst);
	if (!session)
		goto drop;

	dev = manager_get_device(&src, &dst, FALSE);
	if (!dev) {
		dev = manager_get_device(&src, &dst, TRUE);
		if (!dev) {
			error("Unable to get audio device object for %s",
					address);
			goto drop;
		}
	}

	if (dev->control == NULL) {
		btd_device_add_uuid(dev->btd_dev, AVRCP_REMOTE_UUID);
		if (dev->control == NULL)
			goto drop;
	}

	if (session->io) {
		error("Refusing unexpected connect from %s", address);
		goto drop;
	}

	avctp_set_state(session, AVCTP_STATE_CONNECTING);
	session->io = g_io_channel_ref(chan);

	if (audio_device_request_authorization(dev, AVRCP_TARGET_UUID,
						auth_cb, session) < 0)
		goto drop;

	session->io_id = g_io_add_watch(chan, G_IO_ERR | G_IO_HUP | G_IO_NVAL,
							session_cb, session);
	return;

drop:
	if (!session || !session->io)
		g_io_channel_shutdown(chan, TRUE, NULL);
	if (session)
		avctp_set_state(session, AVCTP_STATE_DISCONNECTED);
}
