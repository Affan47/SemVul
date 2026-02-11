check_neigh_update(struct neighbour *neigh)
{
	const struct device *parent;
	const struct net_device *netdev = neigh->dev;

	if (netdev->priv_flags & IFF_802_1Q_VLAN)
		netdev = vlan_dev_real_dev(netdev);
	parent = netdev->dev.parent;
	if (parent && parent->driver == &cxgb4_driver.driver)
		t4_l2t_update(dev_get_drvdata(parent), neigh);
}
