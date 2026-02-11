qlge_get_stats(struct net_device
					       *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);
	struct rx_ring *rx_ring = &qdev->rx_ring[0];
	struct tx_ring *tx_ring = &qdev->tx_ring[0];
	unsigned long pkts, mcast, dropped, errors, bytes;
	int i;


	pkts = mcast = dropped = errors = bytes = 0;
	for (i = 0; i < qdev->rss_ring_count; i++, rx_ring++) {
			pkts += rx_ring->rx_packets;
			bytes += rx_ring->rx_bytes;
			dropped += rx_ring->rx_dropped;
			errors += rx_ring->rx_errors;
			mcast += rx_ring->rx_multicast;
	}
	ndev->stats.rx_packets = pkts;
	ndev->stats.rx_bytes = bytes;
	ndev->stats.rx_dropped = dropped;
	ndev->stats.rx_errors = errors;
	ndev->stats.multicast = mcast;


	pkts = errors = bytes = 0;
	for (i = 0; i < qdev->tx_ring_count; i++, tx_ring++) {
			pkts += tx_ring->tx_packets;
			bytes += tx_ring->tx_bytes;
			errors += tx_ring->tx_errors;
	}
	ndev->stats.tx_packets = pkts;
	ndev->stats.tx_bytes = bytes;
	ndev->stats.tx_errors = errors;
	return &ndev->stats;
}
