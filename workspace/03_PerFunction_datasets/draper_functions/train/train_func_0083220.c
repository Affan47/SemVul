altera_jtaguart_tx_chars(struct altera_jtaguart *pp)
{
	struct uart_port *port = &pp->port;
	struct circ_buf *xmit = &port->state->xmit;
	unsigned int pending, count;

	if (port->x_char) {

		writel(port->x_char, port->membase + ALTERA_JTAGUART_DATA_REG);
		port->x_char = 0;
		port->icount.tx++;
		return;
	}

	pending = uart_circ_chars_pending(xmit);
	if (pending > 0) {
		count = (readl(port->membase + ALTERA_JTAGUART_CONTROL_REG) &
				ALTERA_JTAGUART_CONTROL_WSPACE_MSK) >>
			ALTERA_JTAGUART_CONTROL_WSPACE_OFF;
		if (count > pending)
			count = pending;
		if (count > 0) {
			pending -= count;
			while (count--) {
				writel(xmit->buf[xmit->tail],
				       port->membase + ALTERA_JTAGUART_DATA_REG);
				xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
				port->icount.tx++;
			}
			if (pending < WAKEUP_CHARS)
				uart_write_wakeup(port);
		}
	}

	if (pending == 0) {
		pp->imr &= ~ALTERA_JTAGUART_CONTROL_WE_MSK;
		writel(pp->imr, port->membase + ALTERA_JTAGUART_CONTROL_REG);
	}
}
