pch_uart_set_termios(struct uart_port *port,
				 struct ktermios *termios, struct ktermios *old)
{
	int rtn;
	unsigned int baud, parity, bits, stb;
	struct eg20t_port *priv;
	unsigned long flags;

	priv = container_of(port, struct eg20t_port, port);
	switch (termios->c_cflag & CSIZE) {
	case CS5:
		bits = PCH_UART_HAL_5BIT;
		break;
	case CS6:
		bits = PCH_UART_HAL_6BIT;
		break;
	case CS7:
		bits = PCH_UART_HAL_7BIT;
		break;
	default:
		bits = PCH_UART_HAL_8BIT;
		break;
	}
	if (termios->c_cflag & CSTOPB)
		stb = PCH_UART_HAL_STB2;
	else
		stb = PCH_UART_HAL_STB1;

	if (termios->c_cflag & PARENB) {
		if (termios->c_cflag & PARODD)
			parity = PCH_UART_HAL_PARITY_ODD;
		else
			parity = PCH_UART_HAL_PARITY_EVEN;

	} else
		parity = PCH_UART_HAL_PARITY_NONE;


	if ((termios->c_cflag & CRTSCTS) && (priv->fifo_size == 256))
		priv->mcr |= UART_MCR_AFE;
	else
		priv->mcr &= ~UART_MCR_AFE;

	termios->c_cflag &= ~CMSPAR;

	baud = uart_get_baud_rate(port, termios, old, 0, port->uartclk / 16);

	spin_lock_irqsave(&priv->lock, flags);
	spin_lock(&port->lock);

	uart_update_timeout(port, termios->c_cflag, baud);
	rtn = pch_uart_hal_set_line(priv, baud, parity, bits, stb);
	if (rtn)
		goto out;

	pch_uart_set_mctrl(&priv->port, priv->port.mctrl);

	if (tty_termios_baud_rate(termios))
		tty_termios_encode_baud_rate(termios, baud, baud);

out:
	spin_unlock(&port->lock);
	spin_unlock_irqrestore(&priv->lock, flags);
}
