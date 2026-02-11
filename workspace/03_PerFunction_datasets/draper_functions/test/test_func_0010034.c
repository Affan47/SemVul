set_attr_decimals(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_sevsegdev *mydev = usb_get_intfdata(intf);
	size_t end = my_memlen(buf, count);
	int i;

	if (end > sizeof(mydev->decimals))
		return -EINVAL;

	for (i = 0; i < end; i++)
		if (buf[i] != '0' && buf[i] != '1')
			return -EINVAL;

	memset(mydev->decimals, 0, sizeof(mydev->decimals));
	for (i = 0; i < end; i++)
		if (buf[i] == '1')
			mydev->decimals[end-1-i] = 1;

	update_display_visual(mydev, GFP_KERNEL);

	return count;
}
