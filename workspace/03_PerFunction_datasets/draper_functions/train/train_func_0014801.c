epic_pause(struct net_device *dev)
{
	struct net_device_stats *stats = &dev->stats;
	struct epic_private *ep = netdev_priv(dev);
	void __iomem *ioaddr = ep->ioaddr;

	netif_stop_queue (dev);


	ew32(INTMASK, 0x00000000);

	ew16(COMMAND, StopRx | StopTxDMA | StopRxDMA);


	if (er16(COMMAND) != 0xffff) {
		stats->rx_missed_errors	+= er8(MPCNT);
		stats->rx_frame_errors	+= er8(ALICNT);
		stats->rx_crc_errors	+= er8(CRCCNT);
	}


	epic_rx(dev, RX_RING_SIZE);
}
