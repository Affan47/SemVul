ulite_console_write(struct console *co, const char *s,
				unsigned int count)
{
	struct uart_port *port = &ulite_ports[co->index];
	unsigned long flags;
	unsigned int ier;
	int locked = 1;

	if (oops_in_progress) {
		locked = spin_trylock_irqsave(&port->lock, flags);
	} else
		spin_lock_irqsave(&port->lock, flags);


	ier = uart_in32(ULITE_STATUS, port) & ULITE_STATUS_IE;
	uart_out32(0, ULITE_CONTROL, port);

	uart_console_write(port, s, count, ulite_console_putchar);

	ulite_console_wait_tx(port);


	if (ier)
		uart_out32(ULITE_CONTROL_IE, ULITE_CONTROL, port);

	if (locked)
		spin_unlock_irqrestore(&port->lock, flags);
}
