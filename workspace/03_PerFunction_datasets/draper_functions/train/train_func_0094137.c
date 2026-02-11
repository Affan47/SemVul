fwtty_set_termios(struct tty_struct *tty, struct ktermios *old)
{
	struct fwtty_port *port = tty->driver_data;
	unsigned baud;

	spin_lock_bh(&port->lock);
	baud = set_termios(port, tty);

	if ((baud == 0) && (old->c_cflag & CBAUD)) {
		port->mctrl &= ~(TIOCM_DTR | TIOCM_RTS);
	} else if ((baud != 0) && !(old->c_cflag & CBAUD)) {
		if (C_CRTSCTS(tty) || !test_bit(TTY_THROTTLED, &tty->flags))
			port->mctrl |= TIOCM_DTR | TIOCM_RTS;
		else
			port->mctrl |= TIOCM_DTR;
	}
	__fwtty_write_port_status(port);
	spin_unlock_bh(&port->lock);

	if (old->c_cflag & CRTSCTS) {
		if (!C_CRTSCTS(tty)) {
			tty->hw_stopped = 0;
			fwtty_restart_tx(port);
		}
	} else if (C_CRTSCTS(tty) && ~port->mstatus & TIOCM_CTS) {
		tty->hw_stopped = 1;
	}
}
