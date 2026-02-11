men_z135_get_mctrl(struct uart_port *port)
{
	unsigned int mctrl = 0;
	u8 msr;

	msr = ioread8(port->membase + MEN_Z135_STAT_REG + 1);

	if (msr & MEN_Z135_MSR_CTS)
		mctrl |= TIOCM_CTS;
	if (msr & MEN_Z135_MSR_DSR)
		mctrl |= TIOCM_DSR;
	if (msr & MEN_Z135_MSR_RI)
		mctrl |= TIOCM_RI;
	if (msr & MEN_Z135_MSR_DCD)
		mctrl |= TIOCM_CAR;

	return mctrl;
}
