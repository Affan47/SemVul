asc_transmit_chars(struct uart_port *port)
{
	struct circ_buf *xmit = &port->state->xmit;
	int txroom;
	unsigned char c;

	txroom = asc_hw_txroom(port);

	if ((txroom != 0) && port->x_char) {
		c = port->x_char;
		port->x_char = 0;
		asc_out(port, ASC_TXBUF, c);
		port->icount.tx++;
		txroom = asc_hw_txroom(port);
	}

	if (uart_tx_stopped(port)) {


		asc_disable_tx_interrupts(port);
		return;
	}

	if (uart_circ_empty(xmit)) {
		asc_disable_tx_interrupts(port);
		return;
	}

	if (txroom == 0)
		return;

	do {
		c = xmit->buf[xmit->tail];
		xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
		asc_out(port, ASC_TXBUF, c);
		port->icount.tx++;
		txroom--;
	} while ((txroom > 0) && (!uart_circ_empty(xmit)));

	if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS)
		uart_write_wakeup(port);

	if (uart_circ_empty(xmit))
		asc_disable_tx_interrupts(port);
}
