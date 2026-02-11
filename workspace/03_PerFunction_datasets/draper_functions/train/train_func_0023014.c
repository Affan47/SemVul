destroy_serial(struct kref *kref)
{
	struct usb_serial *serial;
	struct usb_serial_port *port;
	int i;

	serial = to_usb_serial(kref);


	if (serial->minors_reserved)
		release_minors(serial);

	if (serial->attached && serial->type->release)
		serial->type->release(serial);


	for (i = 0; i < serial->num_port_pointers; ++i) {
		port = serial->port[i];
		if (port) {
			port->serial = NULL;
			put_device(&port->dev);
		}
	}

	usb_put_intf(serial->interface);
	usb_put_dev(serial->dev);
	kfree(serial);
}
