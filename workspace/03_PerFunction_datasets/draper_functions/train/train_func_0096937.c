stmmac_set_coalesce(struct net_device *dev,
			       struct ethtool_coalesce *ec)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	unsigned int rx_riwt;


	if ((ec->rx_max_coalesced_frames) || (ec->rx_coalesce_usecs_irq) ||
	    (ec->rx_max_coalesced_frames_irq) || (ec->tx_coalesce_usecs_irq) ||
	    (ec->use_adaptive_rx_coalesce) || (ec->use_adaptive_tx_coalesce) ||
	    (ec->pkt_rate_low) || (ec->rx_coalesce_usecs_low) ||
	    (ec->rx_max_coalesced_frames_low) || (ec->tx_coalesce_usecs_high) ||
	    (ec->tx_max_coalesced_frames_low) || (ec->pkt_rate_high) ||
	    (ec->tx_coalesce_usecs_low) || (ec->rx_coalesce_usecs_high) ||
	    (ec->rx_max_coalesced_frames_high) ||
	    (ec->tx_max_coalesced_frames_irq) ||
	    (ec->stats_block_coalesce_usecs) ||
	    (ec->tx_max_coalesced_frames_high) || (ec->rate_sample_interval))
		return -EOPNOTSUPP;

	if (ec->rx_coalesce_usecs == 0)
		return -EINVAL;

	if ((ec->tx_coalesce_usecs == 0) &&
	    (ec->tx_max_coalesced_frames == 0))
		return -EINVAL;

	if ((ec->tx_coalesce_usecs > STMMAC_MAX_COAL_TX_TICK) ||
	    (ec->tx_max_coalesced_frames > STMMAC_TX_MAX_FRAMES))
		return -EINVAL;

	rx_riwt = stmmac_usec2riwt(ec->rx_coalesce_usecs, priv);

	if ((rx_riwt > MAX_DMA_RIWT) || (rx_riwt < MIN_DMA_RIWT))
		return -EINVAL;
	else if (!priv->use_riwt)
		return -EOPNOTSUPP;


	priv->tx_coal_frames = ec->tx_max_coalesced_frames;
	priv->tx_coal_timer = ec->tx_coalesce_usecs;
	priv->rx_riwt = rx_riwt;
	priv->hw->dma->rx_watchdog(priv->ioaddr, priv->rx_riwt);

	return 0;
}
