usb_serial_device_remove(struct device *dev)
{
	struct usb_serial_driver *driver;
	struct usb_serial_port *port;
	int retval = 0;
	int minor;
	int autopm_err;

	port = to_usb_serial_port(dev);
	if (!port)
		return -ENODEV;


	autopm_err = usb_autopm_get_interface(port->serial->interface);

	minor = port->minor;
	tty_unregister_device(usb_serial_tty_driver, minor);

	driver = port->serial->type;
	if (driver->port_remove)
		retval = driver->port_remove(port);

	dev_info(dev, "%s converter now disconnected from ttyUSB%d\n",
		 driver->description, minor);

	if (!autopm_err)
		usb_autopm_put_interface(port->serial->interface);

	return retval;
}
