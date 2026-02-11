mos7720_close(struct usb_serial_port *port)
{
	struct usb_serial *serial;
	struct moschip_port *mos7720_port;
	int j;

	serial = port->serial;

	mos7720_port = usb_get_serial_port_data(port);
	if (mos7720_port == NULL)
		return;

	for (j = 0; j < NUM_URBS; ++j)
		usb_kill_urb(mos7720_port->write_urb_pool[j]);


	for (j = 0; j < NUM_URBS; ++j) {
		if (mos7720_port->write_urb_pool[j]) {
			kfree(mos7720_port->write_urb_pool[j]->transfer_buffer);
			usb_free_urb(mos7720_port->write_urb_pool[j]);
		}
	}


	usb_kill_urb(port->write_urb);
	usb_kill_urb(port->read_urb);

	write_mos_reg(serial, port->port_number, MOS7720_MCR, 0x00);
	write_mos_reg(serial, port->port_number, MOS7720_IER, 0x00);

	mos7720_port->open = 0;
}
