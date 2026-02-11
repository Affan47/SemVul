attrib_disconnected_cb(GIOChannel *io, GIOCondition cond,
							gpointer user_data)
{
	struct btd_device *device = user_data;
	int sock, err = 0;
	socklen_t len;

	if (device->browse)
		goto done;

	sock = g_io_channel_unix_get_fd(io);
	len = sizeof(err);
	getsockopt(sock, SOL_SOCKET, SO_ERROR, &err, &len);

	g_slist_foreach(device->attios, attio_disconnected, NULL);

	if (device->auto_connect == FALSE || err != ETIMEDOUT)
		goto done;

	device->auto_id = g_timeout_add_seconds_full(G_PRIORITY_DEFAULT_IDLE,
						AUTO_CONNECTION_INTERVAL,
						att_connect, device,
						att_connect_dispatched);

done:
	att_cleanup(device);

	return FALSE;
}
