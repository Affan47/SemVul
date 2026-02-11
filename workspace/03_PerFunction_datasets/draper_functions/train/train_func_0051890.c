mxuport_throttle(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct usb_serial *serial = port->serial;

	dev_dbg(&port->dev, "%s\n", __func__);

	mxuport_send_ctrl_urb(serial, RQ_VENDOR_SET_RX_HOST_EN,
			      0, port->port_number);
}
