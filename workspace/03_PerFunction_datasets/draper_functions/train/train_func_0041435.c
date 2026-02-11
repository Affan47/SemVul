epic_get_stats(struct net_device *dev)
{
	struct epic_private *ep = netdev_priv(dev);
	void __iomem *ioaddr = ep->ioaddr;

	if (netif_running(dev)) {
		struct net_device_stats *stats = &dev->stats;

		stats->rx_missed_errors	+= er8(MPCNT);
		stats->rx_frame_errors	+= er8(ALICNT);
		stats->rx_crc_errors	+= er8(CRCCNT);
	}

	return &dev->stats;
}
