ax88172a_adjust_link(struct net_device *netdev)
{
	struct phy_device *phydev = netdev->phydev;
	struct usbnet *dev = netdev_priv(netdev);
	struct ax88172a_private *priv = dev->driver_priv;
	u16 mode = 0;

	if (phydev->link) {
		mode = AX88772_MEDIUM_DEFAULT;

		if (phydev->duplex == DUPLEX_HALF)
			mode &= ~AX_MEDIUM_FD;

		if (phydev->speed != SPEED_100)
			mode &= ~AX_MEDIUM_PS;
	}

	if (mode != priv->oldmode) {
		asix_write_medium_mode(dev, mode);
		priv->oldmode = mode;
		netdev_dbg(netdev, "speed %u duplex %d, setting mode to 0x%04x\n",
			   phydev->speed, phydev->duplex, mode);
		phy_print_status(phydev);
	}
}
