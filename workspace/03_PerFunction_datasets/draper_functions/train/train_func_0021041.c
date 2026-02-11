smsc95xx_phy_initialize(struct usbnet *dev)
{
	int bmcr, ret, timeout = 0;


	dev->mii.dev = dev->net;
	dev->mii.mdio_read = smsc95xx_mdio_read;
	dev->mii.mdio_write = smsc95xx_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;
	dev->mii.phy_id = SMSC95XX_INTERNAL_PHY_ID;


	smsc95xx_mdio_write(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);

	do {
		msleep(10);
		bmcr = smsc95xx_mdio_read(dev->net, dev->mii.phy_id, MII_BMCR);
		timeout++;
	} while ((bmcr & BMCR_RESET) && (timeout < 100));

	if (timeout >= 100) {
		netdev_warn(dev->net, "timeout on PHY Reset");
		return -EIO;
	}

	smsc95xx_mdio_write(dev->net, dev->mii.phy_id, MII_ADVERTISE,
		ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP |
		ADVERTISE_PAUSE_ASYM);


	ret = smsc95xx_mdio_read(dev->net, dev->mii.phy_id, PHY_INT_SRC);
	if (ret < 0) {
		netdev_warn(dev->net, "Failed to read PHY_INT_SRC during init\n");
		return ret;
	}

	smsc95xx_mdio_write(dev->net, dev->mii.phy_id, PHY_INT_MASK,
		PHY_INT_MASK_DEFAULT_);
	mii_nway_restart(&dev->mii);

	netif_dbg(dev, ifup, dev->net, "phy initialised successfully\n");
	return 0;
}
