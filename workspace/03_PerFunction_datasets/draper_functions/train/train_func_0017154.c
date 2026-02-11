usbvision_i2c_unregister(struct usb_usbvision *usbvision)
{
	if (!usbvision->registered_i2c)
		return 0;

	i2c_del_adapter(&(usbvision->i2c_adap));
	usbvision->registered_i2c = 0;

	PDEBUG(DBG_I2C, "i2c bus for %s unregistered", usbvision->i2c_adap.name);

	return 0;
}
