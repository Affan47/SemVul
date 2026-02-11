rfcomm_connect(struct audio_device *dev, headset_stream_cb_t cb,
				void *user_data, unsigned int *cb_id)
{
	struct headset *hs = dev->headset;
	char address[18];
	GError *err = NULL;

	if (!manager_allow_headset_connection(dev))
		return -ECONNREFUSED;

	if (hs->rfcomm_ch < 0)
		return get_records(dev, cb, user_data, cb_id);

	ba2str(&dev->dst, address);

	DBG("%s: Connecting to %s channel %d", dev->path, address,
		hs->rfcomm_ch);

	hs->tmp_rfcomm = bt_io_connect(BT_IO_RFCOMM, headset_connect_cb, dev,
					NULL, &err,
					BT_IO_OPT_SOURCE_BDADDR, &dev->src,
					BT_IO_OPT_DEST_BDADDR, &dev->dst,
					BT_IO_OPT_CHANNEL, hs->rfcomm_ch,
					BT_IO_OPT_SEC_LEVEL, BT_IO_SEC_MEDIUM,
					BT_IO_OPT_INVALID);

	hs->rfcomm_ch = -1;

	if (!hs->tmp_rfcomm) {
		error("%s", err->message);
		g_error_free(err);
		return -EIO;
	}

	hs->hfp_active = hs->hfp_handle != 0 ? TRUE : FALSE;
	hs->rfcomm_initiator = FALSE;

	headset_set_state(dev, HEADSET_STATE_CONNECTING);

	pending_connect_init(hs, HEADSET_STATE_CONNECTED);

	if (cb) {
		unsigned int id = connect_cb_new(hs, HEADSET_STATE_CONNECTED,
							cb, user_data);
		if (cb_id)
			*cb_id = id;
	}

	return 0;
}
