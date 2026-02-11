of_phy_attach(struct net_device *dev,
				 struct device_node *phy_np, u32 flags,
				 phy_interface_t iface)
{
	struct phy_device *phy = of_phy_find_device(phy_np);
	int ret;

	if (!phy)
		return NULL;

	ret = phy_attach_direct(dev, phy, flags, iface);


	put_device(&phy->dev);

	return ret ? NULL : phy;
}
