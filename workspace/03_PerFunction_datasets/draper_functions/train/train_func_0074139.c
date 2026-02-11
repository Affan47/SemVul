uwb_radio_change_channel(struct uwb_rc *rc, int channel)
{
	int ret = 0;
	struct device *dev = &rc->uwb_dev.dev;

	dev_dbg(dev, "%s: channel = %d, rc->beaconing = %d\n", __func__,
		channel, rc->beaconing);

	if (channel == -1)
		uwb_radio_channel_changed(rc, channel);

	if (channel != rc->beaconing) {
		if (rc->beaconing != -1 && channel != -1) {


			ret = uwb_radio_change_channel(rc, -1);
			if (ret < 0)
				return ret;
		}
		ret = uwb_rc_beacon(rc, channel, 0);
	}

	if (channel != -1)
		uwb_radio_channel_changed(rc, rc->beaconing);

	return ret;
}
