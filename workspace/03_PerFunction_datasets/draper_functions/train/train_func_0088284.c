mac_stats_update(struct adapter *adapter)
{
	int i;

	for_each_port(adapter, i) {
		struct net_device *dev = adapter->port[i];
		struct port_info *p = netdev_priv(dev);

		if (netif_running(dev)) {
			spin_lock(&adapter->stats_lock);
			t3_mac_update_stats(&p->mac);
			spin_unlock(&adapter->stats_lock);
		}
	}
}
