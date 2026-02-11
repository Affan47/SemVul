skge_get_coalesce(struct net_device *dev,
			     struct ethtool_coalesce *ecmd)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int port = skge->port;

	ecmd->rx_coalesce_usecs = 0;
	ecmd->tx_coalesce_usecs = 0;

	if (skge_read32(hw, B2_IRQM_CTRL) & TIM_START) {
		u32 delay = skge_clk2usec(hw, skge_read32(hw, B2_IRQM_INI));
		u32 msk = skge_read32(hw, B2_IRQM_MSK);

		if (msk & rxirqmask[port])
			ecmd->rx_coalesce_usecs = delay;
		if (msk & txirqmask[port])
			ecmd->tx_coalesce_usecs = delay;
	}

	return 0;
}
