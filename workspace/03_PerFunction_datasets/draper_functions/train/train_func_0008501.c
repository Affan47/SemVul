uart_poll_put_char(struct tty_driver *driver, int line, char ch)
{
	struct uart_driver *drv = driver->driver_state;
	struct uart_state *state = drv->state + line;
	struct uart_port *port;

	if (!state || !state->uart_port)
		return;

	port = state->uart_port;

	if (ch == '\n')
		port->ops->poll_put_char(port, '\r');
	port->ops->poll_put_char(port, ch);
}
