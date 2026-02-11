avoid_reset_quirk_store(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct usb_device	*udev = to_usb_device(dev);
	int			val;

	if (sscanf(buf, "%d", &val) != 1 || val < 0 || val > 1)
		return -EINVAL;
	usb_lock_device(udev);
	if (val)
		udev->quirks |= USB_QUIRK_RESET;
	else
		udev->quirks &= ~USB_QUIRK_RESET;
	usb_unlock_device(udev);
	return count;
}
