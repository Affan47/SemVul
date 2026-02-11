skge_set_coalesce(struct net_device *dev,
			     struct ethtool_coalesce *ecmd)
{
	struct skge_port *skge = netdev_priv(dev);
	struct skge_hw *hw = skge->hw;
	int port = skge->port;
	u32 msk = skge_read32(hw, B2_IRQM_MSK);
	u32 delay = 25;

	if (ecmd->rx_coalesce_usecs == 0)
		msk &= ~rxirqmask[port];
	else if (ecmd->rx_coalesce_usecs < 25 ||
		 ecmd->rx_coalesce_usecs > 33333)
		return -EINVAL;
	else {
		msk |= rxirqmask[port];
		delay = ecmd->rx_coalesce_usecs;
	}

	if (ecmd->tx_coalesce_usecs == 0)
		msk &= ~txirqmask[port];
	else if (ecmd->tx_coalesce_usecs < 25 ||
		 ecmd->tx_coalesce_usecs > 33333)
		return -EINVAL;
	else {
		msk |= txirqmask[port];
		delay = min(delay, ecmd->rx_coalesce_usecs);
	}

	skge_write32(hw, B2_IRQM_MSK, msk);
	if (msk == 0)
		skge_write32(hw, B2_IRQM_CTRL, TIM_STOP);
	else {
		skge_write32(hw, B2_IRQM_INI, skge_usecs2clk(hw, delay));
		skge_write32(hw, B2_IRQM_CTRL, TIM_START);
	}
	return 0;
}
