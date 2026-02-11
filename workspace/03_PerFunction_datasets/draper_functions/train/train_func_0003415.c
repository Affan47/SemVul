rp2_ch_interrupt(struct rp2_uart_port *up)
{
	u32 status;

	spin_lock(&up->port.lock);


	status = readl(up->base + RP2_CHAN_STAT);
	writel(status, up->base + RP2_CHAN_STAT);

	if (status & RP2_CHAN_STAT_RXDATA_m)
		rp2_rx_chars(up);
	if (status & RP2_CHAN_STAT_TXEMPTY_m)
		rp2_tx_chars(up);
	if (status & RP2_CHAN_STAT_MS_CHANGED_MASK)
		wake_up_interruptible(&up->port.state->port.delta_msr_wait);

	spin_unlock(&up->port.lock);
}
