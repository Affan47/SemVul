early_serial8250_write(struct console *console,
					const char *s, unsigned int count)
{
	struct earlycon_device *device = console->data;
	struct uart_port *port = &device->port;
	unsigned int ier;


	ier = serial8250_early_in(port, UART_IER);
	if (ier)
		serial8250_early_out(port, UART_IER, ier & UART_IER_UUE);

	uart_console_write(port, s, count, serial_putc);


	wait_for_xmitr(port);

	if (ier)
		serial8250_early_out(port, UART_IER, ier);
}
