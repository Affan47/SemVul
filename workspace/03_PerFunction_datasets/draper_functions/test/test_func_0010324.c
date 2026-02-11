serial8250_console_setup(struct uart_port *port, char *options, bool probe)
{
	int baud = 9600;
	int bits = 8;
	int parity = 'n';
	int flow = 'n';

	if (!port->iobase && !port->membase)
		return -ENODEV;

	if (options)
		uart_parse_options(options, &baud, &parity, &bits, &flow);
	else if (probe)
		baud = probe_baud(port);

	return uart_set_options(port, port->cons, baud, parity, bits, flow);
}
