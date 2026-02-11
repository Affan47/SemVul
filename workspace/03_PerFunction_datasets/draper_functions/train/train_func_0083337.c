imx_rx_dma_done(struct imx_port *sport)
{
	unsigned long temp;
	unsigned long flags;

	spin_lock_irqsave(&sport->port.lock, flags);


	temp = readl(sport->port.membase + UCR1);
	temp |= UCR1_RRDYEN;
	writel(temp, sport->port.membase + UCR1);

	temp = readl(sport->port.membase + UCR2);
	temp |= UCR2_ATEN;
	writel(temp, sport->port.membase + UCR2);

	sport->dma_is_rxing = 0;


	if (waitqueue_active(&sport->dma_wait))
		wake_up(&sport->dma_wait);

	spin_unlock_irqrestore(&sport->port.lock, flags);
}
