usb2_lpm_besl_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	struct usb_device *udev = to_usb_device(dev);
	u8 besl;

	if (kstrtou8(buf, 0, &besl) || besl > 15)
		return -EINVAL;

	udev->l1_params.besl = besl;

	return count;
}
