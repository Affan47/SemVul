serial_port_carrier_raised(struct tty_port *port)
{
	struct usb_serial_port *p = container_of(port, struct usb_serial_port, port);
	struct usb_serial_driver *drv = p->serial->type;

	if (drv->carrier_raised)
		return drv->carrier_raised(p);

	return 1;
}
