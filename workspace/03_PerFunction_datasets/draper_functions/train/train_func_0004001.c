confirm_event_cb(GIOChannel *chan, gpointer user_data)
{
	struct serial_proxy *prx = user_data;
	int perr;
	char address[18];
	GError *err = NULL;

	bt_io_get(chan, BT_IO_RFCOMM, &err,
			BT_IO_OPT_DEST_BDADDR, &prx->dst,
			BT_IO_OPT_DEST, address,
			BT_IO_OPT_INVALID);
	if (err) {
		error("%s", err->message);
		g_error_free(err);
		goto drop;
	}

	if (prx->rfcomm) {
		error("Refusing connect from %s: Proxy already in use",
				address);
		goto drop;
	}

	DBG("Serial Proxy: incoming connect from %s", address);

	prx->rfcomm = g_io_channel_ref(chan);

	perr = btd_request_authorization(&prx->src, &prx->dst,
					prx->uuid128, auth_cb, prx);
	if (perr < 0) {
		error("Refusing connect from %s: %s (%d)", address,
				strerror(-perr), -perr);
		g_io_channel_unref(prx->rfcomm);
		prx->rfcomm = NULL;
		goto drop;
	}

	return;

drop:
	g_io_channel_shutdown(chan, TRUE, NULL);
}
