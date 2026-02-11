ixgbe_set_dcb_queues(struct ixgbe_adapter *adapter)
{
	struct net_device *dev = adapter->netdev;
	struct ixgbe_ring_feature *f;
	int rss_i, rss_m, i;
	int tcs;


	tcs = netdev_get_num_tc(dev);


	if (tcs <= 1)
		return false;


	rss_i = dev->num_tx_queues / tcs;
	if (adapter->hw.mac.type == ixgbe_mac_82598EB) {

		rss_i = min_t(u16, rss_i, 4);
		rss_m = IXGBE_RSS_4Q_MASK;
	} else if (tcs > 4) {

		rss_i = min_t(u16, rss_i, 8);
		rss_m = IXGBE_RSS_8Q_MASK;
	} else {

		rss_i = min_t(u16, rss_i, 16);
		rss_m = IXGBE_RSS_16Q_MASK;
	}


	f = &adapter->ring_feature[RING_F_RSS];
	rss_i = min_t(int, rss_i, f->limit);
	f->indices = rss_i;
	f->mask = rss_m;


	adapter->flags &= ~IXGBE_FLAG_FDIR_HASH_CAPABLE;

#ifdef IXGBE_FCOE


	if (adapter->flags & IXGBE_FLAG_FCOE_ENABLED) {
		u8 tc = ixgbe_fcoe_get_tc(adapter);

		f = &adapter->ring_feature[RING_F_FCOE];
		f->indices = min_t(u16, rss_i, f->limit);
		f->offset = rss_i * tc;
	}

#endif
	for (i = 0; i < tcs; i++)
		netdev_set_tc_queue(dev, i, rss_i, rss_i * i);

	adapter->num_tx_queues = rss_i * tcs;
	adapter->num_rx_queues = rss_i * tcs;

	return true;
}
