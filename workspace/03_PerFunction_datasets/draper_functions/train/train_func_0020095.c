enic_mc_sync(struct net_device *netdev, const u8 *mc_addr)
{
	struct enic *enic = netdev_priv(netdev);

	if (enic->mc_count == ENIC_MULTICAST_PERFECT_FILTERS) {
		unsigned int mc_count = netdev_mc_count(netdev);

		netdev_warn(netdev, "Registering only %d out of %d multicast addresses\n",
			    ENIC_MULTICAST_PERFECT_FILTERS, mc_count);

		return -ENOSPC;
	}

	enic_dev_add_addr(enic, mc_addr);
	enic->mc_count++;

	return 0;
}
