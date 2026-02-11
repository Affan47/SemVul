fwtty_port_activate(struct tty_port *tty_port,
			       struct tty_struct *tty)
{
	struct fwtty_port *port = to_port(tty_port, port);
	unsigned baud;
	int err;

	set_bit(TTY_IO_ERROR, &tty->flags);

	err = dma_fifo_alloc(&port->tx_fifo, FWTTY_PORT_TXFIFO_LEN,
			     cache_line_size(),
			     port->max_payload,
			     FWTTY_PORT_MAX_PEND_DMA,
			     GFP_KERNEL);
	if (err)
		return err;

	spin_lock_bh(&port->lock);

	baud = set_termios(port, tty);


	if (!port->port.console) {
		port->mctrl = 0;
		if (baud != 0)
			port->mctrl = TIOCM_DTR | TIOCM_RTS;
	}

	if (C_CRTSCTS(tty) && ~port->mstatus & TIOCM_CTS)
		tty->hw_stopped = 1;

	__fwtty_write_port_status(port);
	spin_unlock_bh(&port->lock);

	clear_bit(TTY_IO_ERROR, &tty->flags);

	return 0;
}
