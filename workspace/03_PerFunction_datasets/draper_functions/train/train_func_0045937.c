imx_shutdown(struct uart_port *port)
{
	struct imx_port *sport = (struct imx_port *)port;
	unsigned long temp;
	unsigned long flags;

	if (sport->dma_is_enabled) {
		int ret;


		ret = wait_event_interruptible(sport->dma_wait,
			!sport->dma_is_rxing && !sport->dma_is_txing);
		if (ret != 0) {
			sport->dma_is_rxing = 0;
			sport->dma_is_txing = 0;
			dmaengine_terminate_all(sport->dma_chan_tx);
			dmaengine_terminate_all(sport->dma_chan_rx);
		}
		spin_lock_irqsave(&sport->port.lock, flags);
		imx_stop_tx(port);
		imx_stop_rx(port);
		imx_disable_dma(sport);
		spin_unlock_irqrestore(&sport->port.lock, flags);
		imx_uart_dma_exit(sport);
	}

	spin_lock_irqsave(&sport->port.lock, flags);
	temp = readl(sport->port.membase + UCR2);
	temp &= ~(UCR2_TXEN);
	writel(temp, sport->port.membase + UCR2);
	spin_unlock_irqrestore(&sport->port.lock, flags);


	del_timer_sync(&sport->timer);


	spin_lock_irqsave(&sport->port.lock, flags);
	temp = readl(sport->port.membase + UCR1);
	temp &= ~(UCR1_TXMPTYEN | UCR1_RRDYEN | UCR1_RTSDEN | UCR1_UARTEN);

	writel(temp, sport->port.membase + UCR1);
	spin_unlock_irqrestore(&sport->port.lock, flags);

	clk_disable_unprepare(sport->clk_per);
	clk_disable_unprepare(sport->clk_ipg);
}
