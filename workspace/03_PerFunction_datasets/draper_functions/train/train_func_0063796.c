u132_hcd_reset(struct usb_hcd *hcd)
{
	struct u132 *u132 = hcd_to_u132(hcd);
	if (u132->going > 1) {
		dev_err(&u132->platform_dev->dev, "device has been removed %d\n"
			, u132->going);
		return -ENODEV;
	} else if (u132->going > 0) {
		dev_err(&u132->platform_dev->dev, "device is being removed\n");
		return -ESHUTDOWN;
	} else {
		int retval;
		mutex_lock(&u132->sw_lock);
		retval = u132_init(u132);
		if (retval) {
			u132_disable(u132);
			u132->going = 1;
		}
		mutex_unlock(&u132->sw_lock);
		return retval;
	}
}
