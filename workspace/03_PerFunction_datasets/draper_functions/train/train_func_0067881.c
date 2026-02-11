dm9601_bind(struct usbnet *dev, struct usb_interface *intf)
{
	int ret;
	u8 mac[ETH_ALEN], id;

	ret = usbnet_get_endpoints(dev, intf);
	if (ret)
		goto out;

	dev->net->netdev_ops = &dm9601_netdev_ops;
	dev->net->ethtool_ops = &dm9601_ethtool_ops;
	dev->net->hard_header_len += DM_TX_OVERHEAD;
	dev->hard_mtu = dev->net->mtu + dev->net->hard_header_len;


	dev->rx_urb_size = dev->net->mtu + ETH_HLEN + DM_RX_OVERHEAD + 1;

	dev->mii.dev = dev->net;
	dev->mii.mdio_read = dm9601_mdio_read;
	dev->mii.mdio_write = dm9601_mdio_write;
	dev->mii.phy_id_mask = 0x1f;
	dev->mii.reg_num_mask = 0x1f;


	dm_write_reg(dev, DM_NET_CTRL, 1);
	udelay(20);


	if (dm_read(dev, DM_PHY_ADDR, ETH_ALEN, mac) < 0) {
		printk(KERN_ERR "Error reading MAC address\n");
		ret = -ENODEV;
		goto out;
	}


	if (is_valid_ether_addr(mac))
		memcpy(dev->net->dev_addr, mac, ETH_ALEN);
	else {
		printk(KERN_WARNING
			"dm9601: No valid MAC address in EEPROM, using %pM\n",
			dev->net->dev_addr);
		__dm9601_set_mac_address(dev);
	}

	if (dm_read_reg(dev, DM_CHIP_ID, &id) < 0) {
		netdev_err(dev->net, "Error reading chip ID\n");
		ret = -ENODEV;
		goto out;
	}


	if (id == ID_DM9620) {
		u8 mode;

		if (dm_read_reg(dev, DM_MODE_CTRL, &mode) < 0) {
			netdev_err(dev->net, "Error reading MODE_CTRL\n");
			ret = -ENODEV;
			goto out;
		}
		dm_write_reg(dev, DM_MODE_CTRL, mode & 0x7f);
	}


	dm_write_reg(dev, DM_GPR_CTRL, 1);
	dm_write_reg(dev, DM_GPR_DATA, 0);


	dm9601_set_multicast(dev->net);

	dm9601_mdio_write(dev->net, dev->mii.phy_id, MII_BMCR, BMCR_RESET);
	dm9601_mdio_write(dev->net, dev->mii.phy_id, MII_ADVERTISE,
			  ADVERTISE_ALL | ADVERTISE_CSMA | ADVERTISE_PAUSE_CAP);
	mii_nway_restart(&dev->mii);

out:
	return ret;
}
