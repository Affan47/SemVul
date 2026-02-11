bond_delete_netdev_default_gids(struct ib_device *ib_dev,
					    u8 port,
					    struct net_device *event_ndev,
					    struct net_device *rdma_ndev)
{
	struct net_device *real_dev = rdma_vlan_dev_real_dev(event_ndev);

	if (!rdma_ndev)
		return;

	if (!real_dev)
		real_dev = event_ndev;

	rcu_read_lock();

	if (is_upper_dev_rcu(rdma_ndev, event_ndev) &&
	    is_eth_active_slave_of_bonding_rcu(rdma_ndev, real_dev) ==
	    BONDING_SLAVE_STATE_INACTIVE) {
		rcu_read_unlock();

		ib_cache_gid_set_default_gid(ib_dev, port, rdma_ndev,
					     IB_CACHE_GID_DEFAULT_MODE_DELETE);
	} else {
		rcu_read_unlock();
	}
}
