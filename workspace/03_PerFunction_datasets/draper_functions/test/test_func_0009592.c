bnxt_get_channels(struct net_device *dev,
			      struct ethtool_channels *channel)
{
	struct bnxt *bp = netdev_priv(dev);
	int max_rx_rings, max_tx_rings, tcs;

	bnxt_get_max_rings(bp, &max_rx_rings, &max_tx_rings);
	tcs = netdev_get_num_tc(dev);
	if (tcs > 1)
		max_tx_rings /= tcs;

	channel->max_rx = max_rx_rings;
	channel->max_tx = max_tx_rings;
	channel->max_other = 0;
	channel->max_combined = 0;
	channel->rx_count = bp->rx_nr_rings;
	channel->tx_count = bp->tx_nr_rings_per_tc;
}
