ipvlan_open(struct net_device *dev)
{
	struct ipvl_dev *ipvlan = netdev_priv(dev);
	struct net_device *phy_dev = ipvlan->phy_dev;
	struct ipvl_addr *addr;

	if (ipvlan->port->mode == IPVLAN_MODE_L3)
		dev->flags |= IFF_NOARP;
	else
		dev->flags &= ~IFF_NOARP;

	list_for_each_entry(addr, &ipvlan->addrs, anode)
		ipvlan_ht_addr_add(ipvlan, addr);

	return dev_uc_add(phy_dev, phy_dev->dev_addr);
}
