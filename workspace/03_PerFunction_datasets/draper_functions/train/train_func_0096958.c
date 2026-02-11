altera_uart_break_ctl(struct uart_port *port, int break_state)
{
	struct altera_uart *pp = container_of(port, struct altera_uart, port);
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	if (break_state == -1)
		pp->imr |= ALTERA_UART_CONTROL_TRBK_MSK;
	else
		pp->imr &= ~ALTERA_UART_CONTROL_TRBK_MSK;
	altera_uart_writel(port, pp->imr, ALTERA_UART_CONTROL_REG);
	spin_unlock_irqrestore(&port->lock, flags);
}
