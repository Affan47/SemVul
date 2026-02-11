b44_register_phy_one(struct b44 *bp)
{
	struct mii_bus *mii_bus;
	struct ssb_device *sdev = bp->sdev;
	struct phy_device *phydev;
	char bus_id[MII_BUS_ID_SIZE + 3];
	struct ssb_sprom *sprom = &sdev->bus->sprom;
	int err;

	mii_bus = mdiobus_alloc();
	if (!mii_bus) {
		dev_err(sdev->dev, "mdiobus_alloc() failed\n");
		err = -ENOMEM;
		goto err_out;
	}

	mii_bus->priv = bp;
	mii_bus->read = b44_mdio_read_phylib;
	mii_bus->write = b44_mdio_write_phylib;
	mii_bus->name = "b44_eth_mii";
	mii_bus->parent = sdev->dev;
	mii_bus->phy_mask = ~(1 << bp->phy_addr);
	snprintf(mii_bus->id, MII_BUS_ID_SIZE, "%x", instance);
	mii_bus->irq = kmalloc(sizeof(int) * PHY_MAX_ADDR, GFP_KERNEL);
	if (!mii_bus->irq) {
		dev_err(sdev->dev, "mii_bus irq allocation failed\n");
		err = -ENOMEM;
		goto err_out_mdiobus;
	}

	memset(mii_bus->irq, PHY_POLL, sizeof(int) * PHY_MAX_ADDR);

	bp->mii_bus = mii_bus;

	err = mdiobus_register(mii_bus);
	if (err) {
		dev_err(sdev->dev, "failed to register MII bus\n");
		goto err_out_mdiobus_irq;
	}

	if (!bp->mii_bus->phy_map[bp->phy_addr] &&
	    (sprom->boardflags_lo & (B44_BOARDFLAG_ROBO | B44_BOARDFLAG_ADM))) {

		dev_info(sdev->dev,
			 "could not find PHY at %i, use fixed one\n",
			 bp->phy_addr);

		bp->phy_addr = 0;
		snprintf(bus_id, sizeof(bus_id), PHY_ID_FMT, "fixed-0",
			 bp->phy_addr);
	} else {
		snprintf(bus_id, sizeof(bus_id), PHY_ID_FMT, mii_bus->id,
			 bp->phy_addr);
	}

	phydev = phy_connect(bp->dev, bus_id, &b44_adjust_link,
			     PHY_INTERFACE_MODE_MII);
	if (IS_ERR(phydev)) {
		dev_err(sdev->dev, "could not attach PHY at %i\n",
			bp->phy_addr);
		err = PTR_ERR(phydev);
		goto err_out_mdiobus_unregister;
	}


	phydev->supported &= (SUPPORTED_100baseT_Half |
			      SUPPORTED_100baseT_Full |
			      SUPPORTED_Autoneg |
			      SUPPORTED_MII);
	phydev->advertising = phydev->supported;

	bp->phydev = phydev;
	bp->old_link = 0;
	bp->phy_addr = phydev->addr;

	dev_info(sdev->dev, "attached PHY driver [%s] (mii_bus:phy_addr=%s)\n",
		 phydev->drv->name, dev_name(&phydev->dev));

	return 0;

err_out_mdiobus_unregister:
	mdiobus_unregister(mii_bus);

err_out_mdiobus_irq:
	kfree(mii_bus->irq);

err_out_mdiobus:
	mdiobus_free(mii_bus);

err_out:
	return err;
}
