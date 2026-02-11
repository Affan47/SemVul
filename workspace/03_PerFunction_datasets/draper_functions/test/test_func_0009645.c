stmmac_init_phy(struct net_device *dev)
{
	struct stmmac_priv *priv = netdev_priv(dev);
	struct phy_device *phydev;
	char phy_id_fmt[MII_BUS_ID_SIZE + 3];
	char bus_id[MII_BUS_ID_SIZE];
	int interface = priv->plat->interface;
	int max_speed = priv->plat->max_speed;
	priv->oldlink = 0;
	priv->speed = 0;
	priv->oldduplex = -1;

	if (priv->plat->phy_node) {
		phydev = of_phy_connect(dev, priv->plat->phy_node,
					&stmmac_adjust_link, 0, interface);
	} else {
		if (priv->plat->phy_bus_name)
			snprintf(bus_id, MII_BUS_ID_SIZE, "%s-%x",
				 priv->plat->phy_bus_name, priv->plat->bus_id);
		else
			snprintf(bus_id, MII_BUS_ID_SIZE, "stmmac-%x",
				 priv->plat->bus_id);

		snprintf(phy_id_fmt, MII_BUS_ID_SIZE + 3, PHY_ID_FMT, bus_id,
			 priv->plat->phy_addr);
		pr_debug("stmmac_init_phy:  trying to attach to %s\n",
			 phy_id_fmt);

		phydev = phy_connect(dev, phy_id_fmt, &stmmac_adjust_link,
				     interface);
	}

	if (IS_ERR_OR_NULL(phydev)) {
		pr_err("%s: Could not attach to PHY\n", dev->name);
		if (!phydev)
			return -ENODEV;

		return PTR_ERR(phydev);
	}


	if ((interface == PHY_INTERFACE_MODE_MII) ||
	    (interface == PHY_INTERFACE_MODE_RMII) ||
		(max_speed < 1000 && max_speed > 0))
		phydev->advertising &= ~(SUPPORTED_1000baseT_Half |
					 SUPPORTED_1000baseT_Full);


	if (!priv->plat->phy_node && phydev->phy_id == 0) {
		phy_disconnect(phydev);
		return -ENODEV;
	}
	pr_debug("stmmac_init_phy:  %s: attached to PHY (UID 0x%x)"
		 " Link = %d\n", dev->name, phydev->phy_id, phydev->link);

	priv->phydev = phydev;

	return 0;
}
