sco_server_cb(GIOChannel *chan, GError *err, gpointer data)
{
	int sk;
	struct audio_device *device;
	char addr[18];
	bdaddr_t src, dst;

	if (err) {
		error("sco_server_cb: %s", err->message);
		return;
	}

	bt_io_get(chan, BT_IO_SCO, &err,
			BT_IO_OPT_SOURCE_BDADDR, &src,
			BT_IO_OPT_DEST_BDADDR, &dst,
			BT_IO_OPT_DEST, addr,
			BT_IO_OPT_INVALID);
	if (err) {
		error("bt_io_get: %s", err->message);
		goto drop;
	}

	device = manager_find_device(NULL, &src, &dst, AUDIO_HEADSET_INTERFACE,
					FALSE);
	if (!device)
		device = manager_find_device(NULL, &src, &dst,
						AUDIO_GATEWAY_INTERFACE,
						FALSE);

	if (!device)
		goto drop;

	if (device->headset) {
		if (headset_get_state(device) < HEADSET_STATE_CONNECTED) {
			DBG("Refusing SCO from non-connected headset");
			goto gateway;
		}

		if (!headset_get_hfp_active(device)) {
			error("Refusing non-HFP SCO connect attempt from %s",
									addr);
			goto drop;
		}

		if (headset_connect_sco(device, chan) < 0)
			goto drop;

		headset_set_state(device, HEADSET_STATE_PLAYING);
		goto connect;
	}

gateway:
	if (device->gateway) {
		if (!gateway_is_connected(device)) {
			DBG("Refusing SCO from non-connected AG");
			goto drop;
		}

		if (gateway_connect_sco(device, chan) < 0)
			goto drop;
	} else
		goto drop;

connect:
	sk = g_io_channel_unix_get_fd(chan);
	fcntl(sk, F_SETFL, 0);

	DBG("Accepted SCO connection from %s", addr);

	return;

drop:
	g_io_channel_shutdown(chan, TRUE, NULL);
}
