uart_port_startup(struct tty_struct *tty, struct uart_state *state,
		int init_hw)
{
	struct uart_port *uport = state->uart_port;
	unsigned long page;
	int retval = 0;

	if (uport->type == PORT_UNKNOWN)
		return 1;


	uart_change_pm(state, UART_PM_STATE_ON);


	if (!state->xmit.buf) {

		page = get_zeroed_page(GFP_KERNEL);
		if (!page)
			return -ENOMEM;

		state->xmit.buf = (unsigned char *) page;
		uart_circ_clear(&state->xmit);
	}

	retval = uport->ops->startup(uport);
	if (retval == 0) {
		if (uart_console(uport) && uport->cons->cflag) {
			tty->termios.c_cflag = uport->cons->cflag;
			uport->cons->cflag = 0;
		}


		uart_change_speed(tty, state, NULL);

		if (init_hw) {


			if (tty->termios.c_cflag & CBAUD)
				uart_set_mctrl(uport, TIOCM_RTS | TIOCM_DTR);
		}
	}


	if (retval && capable(CAP_SYS_ADMIN))
		return 1;

	return retval;
}
