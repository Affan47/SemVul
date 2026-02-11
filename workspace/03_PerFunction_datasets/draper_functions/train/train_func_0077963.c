usb_serial_generic_tiocmiwait(struct tty_struct *tty, unsigned long arg)
{
	struct usb_serial_port *port = tty->driver_data;
	struct async_icount cnow;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&port->lock, flags);
	cnow = port->icount;
	spin_unlock_irqrestore(&port->lock, flags);

	ret = wait_event_interruptible(port->port.delta_msr_wait,
			usb_serial_generic_msr_changed(tty, arg, &cnow));
	if (!ret && !test_bit(ASYNCB_INITIALIZED, &port->port.flags))
		ret = -EIO;

	return ret;
}
