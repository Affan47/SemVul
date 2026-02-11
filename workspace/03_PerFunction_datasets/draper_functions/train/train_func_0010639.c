keyspan_send_setup(struct usb_serial_port *port, int reset_port)
{
	struct usb_serial *serial = port->serial;
	struct keyspan_serial_private *s_priv;
	const struct keyspan_device_details *d_details;

	s_priv = usb_get_serial_data(serial);
	d_details = s_priv->device_details;

	switch (d_details->msg_format) {
	case msg_usa26:
		keyspan_usa26_send_setup(serial, port, reset_port);
		break;
	case msg_usa28:
		keyspan_usa28_send_setup(serial, port, reset_port);
		break;
	case msg_usa49:
		keyspan_usa49_send_setup(serial, port, reset_port);
		break;
	case msg_usa90:
		keyspan_usa90_send_setup(serial, port, reset_port);
		break;
	case msg_usa67:
		keyspan_usa67_send_setup(serial, port, reset_port);
		break;
	}
}
