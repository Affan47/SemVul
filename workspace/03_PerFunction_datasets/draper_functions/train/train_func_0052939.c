ark3116_tiocmset(struct tty_struct *tty,
			unsigned set, unsigned clr)
{
	struct usb_serial_port *port = tty->driver_data;
	struct ark3116_private *priv = usb_get_serial_port_data(port);


	mutex_lock(&priv->hw_lock);

	if (set & TIOCM_RTS)
		priv->mcr |= UART_MCR_RTS;
	if (set & TIOCM_DTR)
		priv->mcr |= UART_MCR_DTR;
	if (set & TIOCM_OUT1)
		priv->mcr |= UART_MCR_OUT1;
	if (set & TIOCM_OUT2)
		priv->mcr |= UART_MCR_OUT2;
	if (clr & TIOCM_RTS)
		priv->mcr &= ~UART_MCR_RTS;
	if (clr & TIOCM_DTR)
		priv->mcr &= ~UART_MCR_DTR;
	if (clr & TIOCM_OUT1)
		priv->mcr &= ~UART_MCR_OUT1;
	if (clr & TIOCM_OUT2)
		priv->mcr &= ~UART_MCR_OUT2;

	ark3116_write_reg(port->serial, UART_MCR, priv->mcr);

	mutex_unlock(&priv->hw_lock);

	return 0;
}
