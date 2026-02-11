w_resync_timer(struct drbd_work *w, int cancel)
{
	struct drbd_device *device =
		container_of(w, struct drbd_device, resync_work);

	switch (device->state.conn) {
	case C_VERIFY_S:
		make_ov_request(device, cancel);
		break;
	case C_SYNC_TARGET:
		make_resync_request(device, cancel);
		break;
	}

	return 0;
}
