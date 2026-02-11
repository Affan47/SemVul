show_temp(struct device *dev, struct device_attribute *attr, char *buf)
{

	struct usb_interface *intf = to_usb_interface(dev);
	struct usb_cytherm *cytherm = usb_get_intfdata(intf);

	int retval;
	unsigned char *buffer;

	int temp, sign;

	buffer = kmalloc(8, GFP_KERNEL);
	if (!buffer) {
		dev_err(&cytherm->udev->dev, "out of memory\n");
		return 0;
	}


	retval = vendor_command(cytherm->udev, READ_RAM, TEMP, 0, buffer, 8);
	if (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
	temp = buffer[1];


	retval = vendor_command(cytherm->udev, READ_RAM, SIGN, 0, buffer, 8);
	if (retval)
		dev_dbg(&cytherm->udev->dev, "retval = %d\n", retval);
	sign = buffer[1];

	kfree(buffer);

	return sprintf(buf, "%c%i.%i", sign ? '-' : '+', temp >> 1,
		       5*(temp - ((temp >> 1) << 1)));
}
