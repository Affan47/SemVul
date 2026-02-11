sdio_uart_port_get(unsigned index)
{
	struct sdio_uart_port *port;

	if (index >= UART_NR)
		return NULL;

	spin_lock(&sdio_uart_table_lock);
	port = sdio_uart_table[index];
	if (port)
		tty_port_get(&port->port);
	spin_unlock(&sdio_uart_table_lock);

	return port;
}
