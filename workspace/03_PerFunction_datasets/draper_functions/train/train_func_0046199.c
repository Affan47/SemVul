oti6858_tiocmget(struct tty_struct *tty)
{
	struct usb_serial_port *port = tty->driver_data;
	struct oti6858_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;
	unsigned pin_state;
	unsigned result = 0;

	spin_lock_irqsave(&priv->lock, flags);
	pin_state = priv->status.pin_state & PIN_MASK;
	spin_unlock_irqrestore(&priv->lock, flags);


	if ((pin_state & PIN_RTS) != 0)
		result |= TIOCM_RTS;
	if ((pin_state & PIN_CTS) != 0)
		result |= TIOCM_CTS;
	if ((pin_state & PIN_DSR) != 0)
		result |= TIOCM_DSR;
	if ((pin_state & PIN_DTR) != 0)
		result |= TIOCM_DTR;
	if ((pin_state & PIN_RI) != 0)
		result |= TIOCM_RI;
	if ((pin_state & PIN_DCD) != 0)
		result |= TIOCM_CD;

	dev_dbg(&port->dev, "%s() = 0x%08x\n", __func__, result);

	return result;
}
