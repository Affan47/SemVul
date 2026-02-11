lpuart32_get_mctrl(struct uart_port *port)
{
	unsigned int temp = 0;
	unsigned long reg;

	reg = lpuart32_read(port->membase + UARTMODIR);
	if (reg & UARTMODIR_TXCTSE)
		temp |= TIOCM_CTS;

	if (reg & UARTMODIR_RXRTSE)
		temp |= TIOCM_RTS;

	return temp;
}
