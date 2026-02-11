__fwtty_port_line_status(struct fwtty_port *port)
{
	unsigned status = 0;


	if (port->mctrl & TIOCM_DTR)
		status |= TIOCM_DSR | TIOCM_CAR;
	if (port->mctrl & TIOCM_RTS)
		status |= TIOCM_CTS;
	if (port->mctrl & OOB_RX_THROTTLE)
		status |= OOB_TX_THROTTLE;

	if (port->break_ctl)
		status |= UART_LSR_BI << 24;

	return status;
}
