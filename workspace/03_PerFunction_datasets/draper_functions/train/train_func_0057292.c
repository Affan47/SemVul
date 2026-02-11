enic_set_mac_address(struct net_device *netdev, void *p)
{
	struct sockaddr *saddr = p;
	char *addr = saddr->sa_data;
	struct enic *enic = netdev_priv(netdev);
	int err;

	err = enic_dev_del_station_addr(enic);
	if (err)
		return err;

	err = enic_set_mac_addr(netdev, addr);
	if (err)
		return err;

	return enic_dev_add_station_addr(enic);
}
