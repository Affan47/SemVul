sky2_set_ringparam(struct net_device *dev,
			      struct ethtool_ringparam *ering)
{
	struct sky2_port *sky2 = netdev_priv(dev);

	if (ering->rx_pending > RX_MAX_PENDING ||
	    ering->rx_pending < 8 ||
	    ering->tx_pending < TX_MIN_PENDING ||
	    ering->tx_pending > TX_MAX_PENDING)
		return -EINVAL;

	sky2_detach(dev);

	sky2->rx_pending = ering->rx_pending;
	sky2->tx_pending = ering->tx_pending;
	sky2->tx_ring_size = roundup_ring_size(sky2->tx_pending);

	return sky2_reattach(dev);
}
