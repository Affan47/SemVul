ax88172a_init_mdio(struct usbnet *dev)
{
	struct ax88172a_private *priv = dev->driver_priv;
	int ret, i;

	priv->mdio = mdiobus_alloc();
	if (!priv->mdio) {
		netdev_err(dev->net, "Could not allocate MDIO bus\n");
		return -ENOMEM;
	}

	priv->mdio->priv = (void *)dev;
	priv->mdio->read = &asix_mdio_bus_read;
	priv->mdio->write = &asix_mdio_bus_write;
	priv->mdio->name = "Asix MDIO Bus";

	snprintf(priv->mdio->id, MII_BUS_ID_SIZE, "usb-%03d:%03d",
		 dev->udev->bus->busnum, dev->udev->devnum);

	priv->mdio->irq = kzalloc(sizeof(int) * PHY_MAX_ADDR, GFP_KERNEL);
	if (!priv->mdio->irq) {
		ret = -ENOMEM;
		goto mfree;
	}
	for (i = 0; i < PHY_MAX_ADDR; i++)
		priv->mdio->irq[i] = PHY_POLL;

	ret = mdiobus_register(priv->mdio);
	if (ret) {
		netdev_err(dev->net, "Could not register MDIO bus\n");
		goto ifree;
	}

	netdev_info(dev->net, "registered mdio bus %s\n", priv->mdio->id);
	return 0;

ifree:
	kfree(priv->mdio->irq);
mfree:
	mdiobus_free(priv->mdio);
	return ret;
}
