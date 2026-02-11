usb_wwan_ioctl(struct tty_struct *tty,
		   unsigned int cmd, unsigned long arg)
{
	struct usb_serial_port *port = tty->driver_data;

	dev_dbg(&port->dev, "%s cmd 0x%04x\n", __func__, cmd);

	switch (cmd) {
	case TIOCGSERIAL:
		return get_serial_info(port,
				       (struct serial_struct __user *) arg);
	case TIOCSSERIAL:
		return set_serial_info(port,
				       (struct serial_struct __user *) arg);
	default:
		break;
	}

	dev_dbg(&port->dev, "%s arg not supported\n", __func__);

	return -ENOIOCTLCMD;
}
