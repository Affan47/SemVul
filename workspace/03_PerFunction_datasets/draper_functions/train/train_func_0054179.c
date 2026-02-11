sccnxp_set_bit(struct uart_port *port, int sig, int state)
{
	u8 bitmask;
	struct sccnxp_port *s = dev_get_drvdata(port->dev);

	if (s->pdata.mctrl_cfg[port->line] & MCTRL_MASK(sig)) {
		bitmask = 1 << MCTRL_OBIT(s->pdata.mctrl_cfg[port->line], sig);
		if (state)
			sccnxp_write(port, SCCNXP_SOP_REG, bitmask);
		else
			sccnxp_write(port, SCCNXP_ROP_REG, bitmask);
	}
}
