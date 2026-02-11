sdio_uart_send_xchar(struct tty_struct *tty, char ch)
{
	struct sdio_uart_port *port = tty->driver_data;

	port->x_char = ch;
	if (ch && !(port->ier & UART_IER_THRI)) {
		if (sdio_uart_claim_func(port) != 0)
			return;
		sdio_uart_start_tx(port);
		sdio_uart_irq(port->func);
		sdio_uart_release_func(port);
	}
}
