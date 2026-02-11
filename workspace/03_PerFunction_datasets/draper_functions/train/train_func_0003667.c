ssd_init_wmode(struct ssd_device *dev)
{
	int default_wmode;
	int ret = 0;

	if (dev->protocol_info.ver < SSD_PROTOCOL_V3_2) {
		default_wmode = SSD_WMODE_BUFFER;
	} else {
		default_wmode = SSD_WMODE_BUFFER_EX;
	}


	if (SSD_WMODE_AUTO == dev->user_wmode) {

		if (test_bit(SSD_HWMON_PL_CAP(SSD_PL_CAP), &dev->hwmon)) {
			dev->wmode = SSD_WMODE_FUA;
		} else {
			dev->wmode = default_wmode;
		}
	} else if (SSD_WMODE_DEFAULT == dev->user_wmode) {
		dev->wmode = default_wmode;
	} else {
		dev->wmode = dev->user_wmode;
	}
	ssd_set_flush_timeout(dev, dev->wmode);

	return ret;
}
