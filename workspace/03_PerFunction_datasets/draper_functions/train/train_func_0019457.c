uart_chars_in_buffer(struct tty_struct *tty)
{
	struct uart_state *state = tty->driver_data;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&state->uart_port->lock, flags);
	ret = uart_circ_chars_pending(&state->xmit);
	spin_unlock_irqrestore(&state->uart_port->lock, flags);
	return ret;
}
