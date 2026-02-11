mxs_auart_set_mctrl(struct uart_port *u, unsigned mctrl)
{
	struct mxs_auart_port *s = to_auart_port(u);

	u32 ctrl = readl(u->membase + AUART_CTRL2);

	ctrl &= ~(AUART_CTRL2_RTSEN | AUART_CTRL2_RTS);
	if (mctrl & TIOCM_RTS) {
		if (uart_cts_enabled(u))
			ctrl |= AUART_CTRL2_RTSEN;
		else
			ctrl |= AUART_CTRL2_RTS;
	}

	writel(ctrl, u->membase + AUART_CTRL2);

	mctrl_gpio_set(s->gpios, mctrl);
}
