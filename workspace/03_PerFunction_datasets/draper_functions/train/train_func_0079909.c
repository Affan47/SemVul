uwbd_evt_handle_rc_beacon_size(struct uwb_event *evt)
{
	int result = -EINVAL;
	struct device *dev = &evt->rc->uwb_dev.dev;
	struct uwb_rc_evt_beacon_size *bs;


	if (evt->notif.size < sizeof(*bs)) {
		dev_err(dev, "BEACON SIZE notification: Not enough data to "
			"decode (%zu vs %zu bytes needed)\n",
			evt->notif.size, sizeof(*bs));
		goto error;
	}
	bs = container_of(evt->notif.rceb, struct uwb_rc_evt_beacon_size, rceb);
	if (0)
		dev_info(dev, "Beacon size changed to %u bytes "
			"(FIXME: action?)\n", le16_to_cpu(bs->wNewBeaconSize));
	else {

		static unsigned count;
		if (++count % 1000 == 0)
			dev_info(dev, "Beacon size changed %u times "
				"(FIXME: action?)\n", count);
	}
	result = 0;
error:
	return result;
}
