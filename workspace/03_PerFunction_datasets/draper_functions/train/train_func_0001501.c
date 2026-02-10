serial_open(struct tty_struct *tty, struct file *filp)
{
	struct usb_serial_port *port = tty->driver_data;

	dev_dbg(tty->dev, "%s\n", __func__);

	return tty_port_open(&port->port, tty, filp);
}
