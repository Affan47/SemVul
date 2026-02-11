rtl8169_get_stats64(struct net_device *dev, struct rtnl_link_stats64 *stats)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	void __iomem *ioaddr = tp->mmio_addr;
	struct rtl8169_counters *counters = tp->counters;
	unsigned int start;

	if (netif_running(dev))
		rtl8169_rx_missed(dev, ioaddr);

	do {
		start = u64_stats_fetch_begin_irq(&tp->rx_stats.syncp);
		stats->rx_packets = tp->rx_stats.packets;
		stats->rx_bytes	= tp->rx_stats.bytes;
	} while (u64_stats_fetch_retry_irq(&tp->rx_stats.syncp, start));

	do {
		start = u64_stats_fetch_begin_irq(&tp->tx_stats.syncp);
		stats->tx_packets = tp->tx_stats.packets;
		stats->tx_bytes	= tp->tx_stats.bytes;
	} while (u64_stats_fetch_retry_irq(&tp->tx_stats.syncp, start));

	stats->rx_dropped	= dev->stats.rx_dropped;
	stats->tx_dropped	= dev->stats.tx_dropped;
	stats->rx_length_errors = dev->stats.rx_length_errors;
	stats->rx_errors	= dev->stats.rx_errors;
	stats->rx_crc_errors	= dev->stats.rx_crc_errors;
	stats->rx_fifo_errors	= dev->stats.rx_fifo_errors;
	stats->rx_missed_errors = dev->stats.rx_missed_errors;
	stats->multicast	= dev->stats.multicast;


	rtl8169_update_counters(dev);


	stats->tx_errors = le64_to_cpu(counters->tx_errors) -
		le64_to_cpu(tp->tc_offset.tx_errors);
	stats->collisions = le32_to_cpu(counters->tx_multi_collision) -
		le32_to_cpu(tp->tc_offset.tx_multi_collision);
	stats->tx_aborted_errors = le16_to_cpu(counters->tx_aborted) -
		le16_to_cpu(tp->tc_offset.tx_aborted);

	return stats;
}
