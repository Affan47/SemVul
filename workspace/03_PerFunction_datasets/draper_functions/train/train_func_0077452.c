serial_console_write(struct console *co, const char *s,
				 unsigned count)
{
	struct sci_port *sci_port = &sci_ports[co->index];
	struct uart_port *port = &sci_port->port;
	unsigned short bits, ctrl;
	unsigned long flags;
	int locked = 1;

	local_irq_save(flags);
	if (port->sysrq)
		locked = 0;
	else if (oops_in_progress)
		locked = spin_trylock(&port->lock);
	else
		spin_lock(&port->lock);


	ctrl = serial_port_in(port, SCSCR);
	serial_port_out(port, SCSCR, sci_port->cfg->scscr);

	uart_console_write(port, s, count, serial_console_putchar);


	bits = SCxSR_TDxE(port) | SCxSR_TEND(port);
	while ((serial_port_in(port, SCxSR) & bits) != bits)
		cpu_relax();


	serial_port_out(port, SCSCR, ctrl);

	if (locked)
		spin_unlock(&port->lock);
	local_irq_restore(flags);
}
