uart_set_ldisc(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	struct uart_port *uport = state->uart_port;

	if (uport->ops->set_ldisc) {
		mutex_lock(&state->port.mutex);
		uport->ops->set_ldisc(uport, &tty->termios);
		mutex_unlock(&state->port.mutex);
	}
}
