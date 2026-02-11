ch341_tiocmset(struct tty_struct *tty,
			  unsigned int set, unsigned int clear)
{
	struct usb_serial_port *port = tty->driver_data;
	struct ch341_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;
	u8 control;

	spin_lock_irqsave(&priv->lock, flags);
	if (set & TIOCM_RTS)
		priv->line_control |= CH341_BIT_RTS;
	if (set & TIOCM_DTR)
		priv->line_control |= CH341_BIT_DTR;
	if (clear & TIOCM_RTS)
		priv->line_control &= ~CH341_BIT_RTS;
	if (clear & TIOCM_DTR)
		priv->line_control &= ~CH341_BIT_DTR;
	control = priv->line_control;
	spin_unlock_irqrestore(&priv->lock, flags);

	return ch341_set_handshake(port->serial->dev, control);
}
