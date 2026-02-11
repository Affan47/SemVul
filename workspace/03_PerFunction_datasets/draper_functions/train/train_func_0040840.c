atmel_stop_rx(struct uart_port *port)
{
	atmel_uart_writel(port, ATMEL_US_CR, ATMEL_US_RXDIS);

	if (atmel_use_pdc_rx(port)) {

		atmel_uart_writel(port, ATMEL_PDC_PTCR, ATMEL_PDC_RXTDIS);
		atmel_uart_writel(port, ATMEL_US_IDR,
				  ATMEL_US_ENDRX | ATMEL_US_TIMEOUT |
				  port->read_status_mask);
	} else {
		atmel_uart_writel(port, ATMEL_US_IDR, ATMEL_US_RXRDY);
	}
}
