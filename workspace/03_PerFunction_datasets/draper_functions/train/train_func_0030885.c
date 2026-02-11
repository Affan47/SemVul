imx_startup(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	int retval, i;
	unsigned long flags, temp;

	retval = clk_prepare_enable(sport->clk_per);
	if (retval)
		return retval;
	retval = clk_prepare_enable(sport->clk_ipg);
	if (retval) {
		clk_disable_unprepare(sport->clk_per);
		return retval;
	}

	imx_setup_ufcr(sport, TXTL_DEFAULT, RXTL_DEFAULT);


	temp = readl(sport->port.membase + UCR4);


	temp &= ~(UCR4_CTSTL_MASK << UCR4_CTSTL_SHF);
	temp |= CTSTL << UCR4_CTSTL_SHF;

	writel(temp & ~UCR4_DREN, sport->port.membase + UCR4);


	if (is_imx6q_uart(sport) && !uart_console(port) &&
	    !sport->dma_is_inited)
		imx_uart_dma_init(sport);

	spin_lock_irqsave(&sport->port.lock, flags);

	i = 100;

	temp = readl(sport->port.membase + UCR2);
	temp &= ~UCR2_SRST;
	writel(temp, sport->port.membase + UCR2);

	while (!(readl(sport->port.membase + UCR2) & UCR2_SRST) && (--i > 0))
		udelay(1);


	writel(USR1_RTSD, sport->port.membase + USR1);
	writel(USR2_ORE, sport->port.membase + USR2);

	if (sport->dma_is_inited && !sport->dma_is_enabled)
		imx_enable_dma(sport);

	temp = readl(sport->port.membase + UCR1);
	temp |= UCR1_RRDYEN | UCR1_RTSDEN | UCR1_UARTEN;

	writel(temp, sport->port.membase + UCR1);

	temp = readl(sport->port.membase + UCR4);
	temp |= UCR4_OREN;
	writel(temp, sport->port.membase + UCR4);

	temp = readl(sport->port.membase + UCR2);
	temp |= (UCR2_RXEN | UCR2_TXEN);
	if (!sport->have_rtscts)
		temp |= UCR2_IRTS;
	writel(temp, sport->port.membase + UCR2);

	if (!is_imx1_uart(sport)) {
		temp = readl(sport->port.membase + UCR3);
		temp |= IMX21_UCR3_RXDMUXSEL | UCR3_ADNIMP;
		writel(temp, sport->port.membase + UCR3);
	}


	imx_enable_ms(&sport->port);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	return 0;
}
