cbaf_wusb_host_name_store(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t size)
{
	ssize_t result;
	struct usb_interface *iface = to_usb_interface(dev);
	struct cbaf *cbaf = usb_get_intfdata(iface);

	result = sscanf(buf, "%63s", cbaf->host_name);
	if (result != 1)
		return -EINVAL;

	return size;
}
