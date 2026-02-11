sc16is7xx_handle_rx(struct uart_port *port, unsigned int rxlen,
				unsigned int iir)
{
	struct sc16is7xx_port *s = dev_get_drvdata(port->dev);
	unsigned int lsr = 0, ch, flag, bytes_read, i;
	bool read_lsr = (iir == SC16IS7XX_IIR_RLSE_SRC) ? true : false;

	if (unlikely(rxlen >= sizeof(s->buf))) {
		dev_warn_ratelimited(port->dev,
				     "ttySC%i: Possible RX FIFO overrun: %d\n",
				     port->line, rxlen);
		port->icount.buf_overrun++;

		rxlen = sizeof(s->buf);
	}

	while (rxlen) {

		if (read_lsr) {
			lsr = sc16is7xx_port_read(port, SC16IS7XX_LSR_REG);
			if (!(lsr & SC16IS7XX_LSR_FIFOE_BIT))
				read_lsr = false;
		} else
			lsr = 0;

		if (read_lsr) {
			s->buf[0] = sc16is7xx_port_read(port, SC16IS7XX_RHR_REG);
			bytes_read = 1;
		} else {
			sc16is7xx_fifo_read(port, rxlen);
			bytes_read = rxlen;
		}

		lsr &= SC16IS7XX_LSR_BRK_ERROR_MASK;

		port->icount.rx++;
		flag = TTY_NORMAL;

		if (unlikely(lsr)) {
			if (lsr & SC16IS7XX_LSR_BI_BIT) {
				port->icount.brk++;
				if (uart_handle_break(port))
					continue;
			} else if (lsr & SC16IS7XX_LSR_PE_BIT)
				port->icount.parity++;
			else if (lsr & SC16IS7XX_LSR_FE_BIT)
				port->icount.frame++;
			else if (lsr & SC16IS7XX_LSR_OE_BIT)
				port->icount.overrun++;

			lsr &= port->read_status_mask;
			if (lsr & SC16IS7XX_LSR_BI_BIT)
				flag = TTY_BREAK;
			else if (lsr & SC16IS7XX_LSR_PE_BIT)
				flag = TTY_PARITY;
			else if (lsr & SC16IS7XX_LSR_FE_BIT)
				flag = TTY_FRAME;
			else if (lsr & SC16IS7XX_LSR_OE_BIT)
				flag = TTY_OVERRUN;
		}

		for (i = 0; i < bytes_read; ++i) {
			ch = s->buf[i];
			if (uart_handle_sysrq_char(port, ch))
				continue;

			if (lsr & port->ignore_status_mask)
				continue;

			uart_insert_char(port, lsr, SC16IS7XX_LSR_OE_BIT, ch,
					 flag);
		}
		rxlen -= bytes_read;
	}

	tty_flip_buffer_push(&port->state->port);
}
