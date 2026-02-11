atmel_flush_buffer(struct uart_port *port)
{
	struct atmel_uart_port *atmel_port = to_atmel_uart_port(port);

	if (atmel_use_pdc_tx(port)) {
		atmel_uart_writel(port, ATMEL_PDC_TCR, 0);
		atmel_port->pdc_tx.ofs = 0;
	}


	atmel_port->tx_len = 0;
}
