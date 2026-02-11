dw8250_setup_port(struct uart_port *p)
{
	struct uart_8250_port *up = up_to_u8250p(p);
	u32 reg;


	reg = readl(p->membase + DW_UART_UCV);
	if (!reg)
		return;

	dev_dbg(p->dev, "Designware UART version %c.%c%c\n",
		(reg >> 24) & 0xff, (reg >> 16) & 0xff, (reg >> 8) & 0xff);

	reg = readl(p->membase + DW_UART_CPR);
	if (!reg)
		return;


	if (reg & DW_UART_CPR_FIFO_MODE) {
		p->type = PORT_16550A;
		p->flags |= UPF_FIXED_TYPE;
		p->fifosize = DW_UART_CPR_FIFO_SIZE(reg);
		up->capabilities = UART_CAP_FIFO;
	}

	if (reg & DW_UART_CPR_AFCE_MODE)
		up->capabilities |= UART_CAP_AFE;
}
