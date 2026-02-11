ssu100_update_lsr(struct usb_serial_port *port, u8 lsr,
			      char *tty_flag)
{
	struct ssu100_port_private *priv = usb_get_serial_port_data(port);
	unsigned long flags;

	spin_lock_irqsave(&priv->status_lock, flags);
	priv->shadowLSR = lsr;
	spin_unlock_irqrestore(&priv->status_lock, flags);

	*tty_flag = TTY_NORMAL;
	if (lsr & UART_LSR_BRK_ERROR_BITS) {


		if (lsr & UART_LSR_BI) {
			port->icount.brk++;
			*tty_flag = TTY_BREAK;
			usb_serial_handle_break(port);
		}
		if (lsr & UART_LSR_PE) {
			port->icount.parity++;
			if (*tty_flag == TTY_NORMAL)
				*tty_flag = TTY_PARITY;
		}
		if (lsr & UART_LSR_FE) {
			port->icount.frame++;
			if (*tty_flag == TTY_NORMAL)
				*tty_flag = TTY_FRAME;
		}
		if (lsr & UART_LSR_OE) {
			port->icount.overrun++;
			tty_insert_flip_char(&port->port, 0, TTY_OVERRUN);
		}
	}

}
