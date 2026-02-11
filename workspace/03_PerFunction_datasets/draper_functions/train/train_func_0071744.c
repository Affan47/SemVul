max310x_handle_rx(struct uart_port *port, unsigned int rxlen)
{
	unsigned int sts, ch, flag;

	if (unlikely(rxlen >= port->fifosize)) {
		dev_warn_ratelimited(port->dev,
				     "Port %i: Possible RX FIFO overrun\n",
				     port->line);
		port->icount.buf_overrun++;

		rxlen = port->fifosize;
	}

	while (rxlen--) {
		ch = max310x_port_read(port, MAX310X_RHR_REG);
		sts = max310x_port_read(port, MAX310X_LSR_IRQSTS_REG);

		sts &= MAX310X_LSR_RXPAR_BIT | MAX310X_LSR_FRERR_BIT |
		       MAX310X_LSR_RXOVR_BIT | MAX310X_LSR_RXBRK_BIT;

		port->icount.rx++;
		flag = TTY_NORMAL;

		if (unlikely(sts)) {
			if (sts & MAX310X_LSR_RXBRK_BIT) {
				port->icount.brk++;
				if (uart_handle_break(port))
					continue;
			} else if (sts & MAX310X_LSR_RXPAR_BIT)
				port->icount.parity++;
			else if (sts & MAX310X_LSR_FRERR_BIT)
				port->icount.frame++;
			else if (sts & MAX310X_LSR_RXOVR_BIT)
				port->icount.overrun++;

			sts &= port->read_status_mask;
			if (sts & MAX310X_LSR_RXBRK_BIT)
				flag = TTY_BREAK;
			else if (sts & MAX310X_LSR_RXPAR_BIT)
				flag = TTY_PARITY;
			else if (sts & MAX310X_LSR_FRERR_BIT)
				flag = TTY_FRAME;
			else if (sts & MAX310X_LSR_RXOVR_BIT)
				flag = TTY_OVERRUN;
		}

		if (uart_handle_sysrq_char(port, ch))
			continue;

		if (sts & port->ignore_status_mask)
			continue;

		uart_insert_char(port, sts, MAX310X_LSR_RXOVR_BIT, ch, flag);
	}

	tty_flip_buffer_push(&port->state->port);
}
