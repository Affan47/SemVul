arc_serial_tx_empty(struct uart_port *port)
{
	unsigned int stat;

	stat = UART_GET_STATUS(port);
	if (stat & TXEMPTY)
		return TIOCSER_TEMT;

	return 0;
}
