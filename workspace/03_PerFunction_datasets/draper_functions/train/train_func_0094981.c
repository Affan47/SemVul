gem_get_settings(struct net_device *dev, struct ethtool_cmd *cmd)
{
	struct gem *gp = netdev_priv(dev);

	if (gp->phy_type == phy_mii_mdio0 ||
	    gp->phy_type == phy_mii_mdio1) {
		if (gp->phy_mii.def)
			cmd->supported = gp->phy_mii.def->features;
		else
			cmd->supported = (SUPPORTED_10baseT_Half |
					  SUPPORTED_10baseT_Full);


		cmd->port = PORT_MII;
		cmd->transceiver = XCVR_EXTERNAL;
		cmd->phy_address = 0;


		cmd->autoneg = gp->want_autoneg;
		ethtool_cmd_speed_set(cmd, gp->phy_mii.speed);
		cmd->duplex = gp->phy_mii.duplex;
		cmd->advertising = gp->phy_mii.advertising;


		if (cmd->advertising == 0)
			cmd->advertising = cmd->supported;
	} else {
		cmd->supported =
			(SUPPORTED_10baseT_Half | SUPPORTED_10baseT_Full |
			 SUPPORTED_100baseT_Half | SUPPORTED_100baseT_Full |
			 SUPPORTED_Autoneg);
		cmd->advertising = cmd->supported;
		ethtool_cmd_speed_set(cmd, 0);
		cmd->duplex = cmd->port = cmd->phy_address =
			cmd->transceiver = cmd->autoneg = 0;


		if (gp->phy_type == phy_serdes) {
			cmd->port = PORT_FIBRE;
			cmd->supported = (SUPPORTED_1000baseT_Half |
				SUPPORTED_1000baseT_Full |
				SUPPORTED_FIBRE | SUPPORTED_Autoneg |
				SUPPORTED_Pause | SUPPORTED_Asym_Pause);
			cmd->advertising = cmd->supported;
			cmd->transceiver = XCVR_INTERNAL;
			if (gp->lstate == link_up)
				ethtool_cmd_speed_set(cmd, SPEED_1000);
			cmd->duplex = DUPLEX_FULL;
			cmd->autoneg = 1;
		}
	}
	cmd->maxtxpkt = cmd->maxrxpkt = 0;

	return 0;
}
