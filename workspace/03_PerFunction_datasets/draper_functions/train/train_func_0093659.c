serial8250_get_mctrl(struct uart_port *port)
{
	struct uart_8250_port *up = up_to_u8250p(port);
	unsigned int status;
	unsigned int ret;

	serial8250_rpm_get(up);
	status = serial8250_modem_status(up);
	serial8250_rpm_put(up);

	ret = 0;
	if (status & UART_MSR_DCD)
		ret |= TIOCM_CAR;
	if (status & UART_MSR_RI)
		ret |= TIOCM_RNG;
	if (status & UART_MSR_DSR)
		ret |= TIOCM_DSR;
	if (status & UART_MSR_CTS)
		ret |= TIOCM_CTS;
	return ret;
}
