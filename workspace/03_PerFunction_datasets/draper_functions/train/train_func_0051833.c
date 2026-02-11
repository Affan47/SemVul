stm32_receive_chars(struct uart_port *port)
{
	struct tty_port *tport = &port->state->port;
	unsigned long c;
	u32 sr;
	char flag;

	if (port->irq_wake)
		pm_wakeup_event(tport->tty->dev, 0);

	while ((sr = readl_relaxed(port->membase + USART_SR)) & USART_SR_RXNE) {
		sr |= USART_SR_DUMMY_RX;
		c = readl_relaxed(port->membase + USART_DR);
		flag = TTY_NORMAL;
		port->icount.rx++;

		if (sr & USART_SR_ERR_MASK) {
			if (sr & USART_SR_LBD) {
				port->icount.brk++;
				if (uart_handle_break(port))
					continue;
			} else if (sr & USART_SR_ORE) {
				port->icount.overrun++;
			} else if (sr & USART_SR_PE) {
				port->icount.parity++;
			} else if (sr & USART_SR_FE) {
				port->icount.frame++;
			}

			sr &= port->read_status_mask;

			if (sr & USART_SR_LBD)
				flag = TTY_BREAK;
			else if (sr & USART_SR_PE)
				flag = TTY_PARITY;
			else if (sr & USART_SR_FE)
				flag = TTY_FRAME;
		}

		if (uart_handle_sysrq_char(port, c))
			continue;
		uart_insert_char(port, sr, USART_SR_ORE, c, flag);
	}

	spin_unlock(&port->lock);
	tty_flip_buffer_push(tport);
	spin_lock(&port->lock);
}
