phy_connect(struct net_device *dev, const char *bus_id,
			       void (*handler)(struct net_device *),
			       phy_interface_t interface)
{
	struct phy_device *phydev;
	struct device *d;
	int rc;


	d = bus_find_device_by_name(&mdio_bus_type, NULL, bus_id);
	if (!d) {
		pr_err("PHY %s not found\n", bus_id);
		return ERR_PTR(-ENODEV);
	}
	phydev = to_phy_device(d);

	rc = phy_connect_direct(dev, phydev, handler, interface);
	if (rc)
		return ERR_PTR(rc);

	return phydev;
}
