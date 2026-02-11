univ8250_release_irq(struct uart_8250_port *up)
{
	struct uart_port *port = &up->port;

	del_timer_sync(&up->timer);
	up->timer.function = serial8250_timeout;
	if (port->irq)
		serial_unlink_irq_chain(up);
}
