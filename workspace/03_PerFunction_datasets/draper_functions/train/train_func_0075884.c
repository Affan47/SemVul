mwl8k_rx_poll(unsigned long data)
{
	struct ieee80211_hw *hw = (struct ieee80211_hw *)data;
	struct mwl8k_priv *priv = hw->priv;
	int limit;

	limit = 32;
	limit -= rxq_process(hw, 0, limit);
	limit -= rxq_refill(hw, 0, limit);

	if (limit) {
		writel(~MWL8K_A2H_INT_RX_READY,
		       priv->regs + MWL8K_HIU_A2H_INTERRUPT_STATUS);
	} else {
		tasklet_schedule(&priv->poll_rx_task);
	}
}
