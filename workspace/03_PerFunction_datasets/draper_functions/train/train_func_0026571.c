qlcnic_get_ethtool_stats(struct net_device *dev,
				     struct ethtool_stats *stats, u64 *data)
{
	struct qlcnic_adapter *adapter = netdev_priv(dev);
	struct qlcnic_host_tx_ring *tx_ring;
	struct qlcnic_esw_statistics port_stats;
	struct qlcnic_mac_statistics mac_stats;
	int index, ret, length, size, ring;
	char *p;

	memset(data, 0, stats->n_stats * sizeof(u64));

	for (ring = 0, index = 0; ring < adapter->drv_tx_rings; ring++) {
		if (adapter->is_up == QLCNIC_ADAPTER_UP_MAGIC) {
			tx_ring = &adapter->tx_ring[ring];
			data = qlcnic_fill_tx_queue_stats(data, tx_ring);
			qlcnic_update_stats(adapter);
		} else {
			data += QLCNIC_TX_STATS_LEN;
		}
	}

	length = QLCNIC_STATS_LEN;
	for (index = 0; index < length; index++) {
		p = (char *)adapter + qlcnic_gstrings_stats[index].stat_offset;
		size = qlcnic_gstrings_stats[index].sizeof_stat;
		*data++ = (size == sizeof(u64)) ? (*(u64 *)p) : ((*(u32 *)p));
	}

	if (qlcnic_83xx_check(adapter)) {
		if (adapter->ahw->linkup)
			qlcnic_83xx_get_stats(adapter, data);
		return;
	} else {

		memset(&mac_stats, 0, sizeof(struct qlcnic_mac_statistics));
		qlcnic_get_mac_stats(adapter, &mac_stats);
		data = qlcnic_fill_stats(data, &mac_stats, QLCNIC_MAC_STATS);
	}

	if (!(adapter->flags & QLCNIC_ESWITCH_ENABLED))
		return;

	memset(&port_stats, 0, sizeof(struct qlcnic_esw_statistics));
	ret = qlcnic_get_port_stats(adapter, adapter->ahw->pci_func,
			QLCNIC_QUERY_RX_COUNTER, &port_stats.rx);
	if (ret)
		return;

	data = qlcnic_fill_stats(data, &port_stats.rx, QLCNIC_ESW_STATS);
	ret = qlcnic_get_port_stats(adapter, adapter->ahw->pci_func,
			QLCNIC_QUERY_TX_COUNTER, &port_stats.tx);
	if (ret)
		return;

	qlcnic_fill_stats(data, &port_stats.tx, QLCNIC_ESW_STATS);
}
