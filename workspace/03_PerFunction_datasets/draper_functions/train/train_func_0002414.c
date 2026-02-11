cbaf_wusb_ck_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t size)
{
	ssize_t result;
	struct usb_interface *iface = to_usb_interface(dev);
	struct cbaf *cbaf = usb_get_intfdata(iface);

	result = sscanf(buf,
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx",
			&cbaf->ck.data[0] , &cbaf->ck.data[1],
			&cbaf->ck.data[2] , &cbaf->ck.data[3],
			&cbaf->ck.data[4] , &cbaf->ck.data[5],
			&cbaf->ck.data[6] , &cbaf->ck.data[7],
			&cbaf->ck.data[8] , &cbaf->ck.data[9],
			&cbaf->ck.data[10], &cbaf->ck.data[11],
			&cbaf->ck.data[12], &cbaf->ck.data[13],
			&cbaf->ck.data[14], &cbaf->ck.data[15]);
	if (result != 16)
		return -EINVAL;

	result = cbaf_cc_upload(cbaf);
	if (result < 0)
		return result;

	return size;
}
