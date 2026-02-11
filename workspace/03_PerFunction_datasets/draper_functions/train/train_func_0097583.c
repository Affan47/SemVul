netdev_set_ecmd(struct net_device *dev, struct ethtool_cmd *ecmd)
{
	struct netdev_private *np = netdev_priv(dev);

	if (ecmd->port != PORT_TP && ecmd->port != PORT_MII && ecmd->port != PORT_FIBRE)
		return -EINVAL;
	if (ecmd->transceiver != XCVR_INTERNAL && ecmd->transceiver != XCVR_EXTERNAL)
		return -EINVAL;
	if (ecmd->autoneg == AUTONEG_ENABLE) {
		if ((ecmd->advertising & (ADVERTISED_10baseT_Half |
					  ADVERTISED_10baseT_Full |
					  ADVERTISED_100baseT_Half |
					  ADVERTISED_100baseT_Full)) == 0) {
			return -EINVAL;
		}
	} else if (ecmd->autoneg == AUTONEG_DISABLE) {
		u32 speed = ethtool_cmd_speed(ecmd);
		if (speed != SPEED_10 && speed != SPEED_100)
			return -EINVAL;
		if (ecmd->duplex != DUPLEX_HALF && ecmd->duplex != DUPLEX_FULL)
			return -EINVAL;
	} else {
		return -EINVAL;
	}


	if (np->ignore_phy && (ecmd->autoneg == AUTONEG_ENABLE ||
			       ecmd->port == PORT_TP))
		return -EINVAL;


	dev->if_port          = ecmd->port;
	np->autoneg           = ecmd->autoneg;
	np->phy_addr_external = ecmd->phy_address & PhyAddrMask;
	if (np->autoneg == AUTONEG_ENABLE) {

		np->advertising &= ~(ADVERTISE_ALL | ADVERTISE_100BASE4);
		if (ecmd->advertising & ADVERTISED_10baseT_Half)
			np->advertising |= ADVERTISE_10HALF;
		if (ecmd->advertising & ADVERTISED_10baseT_Full)
			np->advertising |= ADVERTISE_10FULL;
		if (ecmd->advertising & ADVERTISED_100baseT_Half)
			np->advertising |= ADVERTISE_100HALF;
		if (ecmd->advertising & ADVERTISED_100baseT_Full)
			np->advertising |= ADVERTISE_100FULL;
	} else {
		np->speed  = ethtool_cmd_speed(ecmd);
		np->duplex = ecmd->duplex;

		if (np->duplex == DUPLEX_HALF)
			np->full_duplex = 0;
	}


	if (ecmd->port == PORT_TP)
		switch_port_internal(dev);
	else
		switch_port_external(dev);


	init_phy_fixup(dev);
	check_link(dev);
	return 0;
}
