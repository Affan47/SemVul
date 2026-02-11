hns_mdio_read(struct mii_bus *bus, int phy_id, int regnum)
{
	int ret;
	u16 reg_val = 0;
	u8 devad = ((regnum >> 16) & 0x1f);
	u8 is_c45 = !!(regnum & MII_ADDR_C45);
	u16 reg = (u16)(regnum & 0xffff);
	struct hns_mdio_device *mdio_dev = (struct hns_mdio_device *)bus->priv;

	dev_dbg(&bus->dev, "mdio read %s,base is %p\n",
		bus->id, mdio_dev->vbase);
	dev_dbg(&bus->dev, "phy id=%d, is_c45=%d, devad=%d, reg=%#x!\n",
		phy_id, is_c45, devad, reg);


	ret = hns_mdio_wait_ready(bus);
	if (ret) {
		dev_err(&bus->dev, "MDIO bus is busy\n");
		return ret;
	}

	if (!is_c45) {
		hns_mdio_cmd_write(mdio_dev, is_c45,
				   MDIO_C22_READ, phy_id, reg);
	} else {
		MDIO_SET_REG_FIELD(mdio_dev, MDIO_ADDR_REG, MDIO_ADDR_DATA_M,
				   MDIO_ADDR_DATA_S, reg);


		hns_mdio_cmd_write(mdio_dev, is_c45,
				   MDIO_C45_WRITE_ADDR, phy_id, devad);


		ret = hns_mdio_wait_ready(bus);
		if (ret) {
			dev_err(&bus->dev, "MDIO bus is busy\n");
			return ret;
		}

		hns_mdio_cmd_write(mdio_dev, is_c45,
				   MDIO_C45_WRITE_ADDR, phy_id, devad);
	}


	ret = hns_mdio_wait_ready(bus);
	if (ret) {
		dev_err(&bus->dev, "MDIO bus is busy\n");
		return ret;
	}

	reg_val = MDIO_GET_REG_BIT(mdio_dev, MDIO_STA_REG, MDIO_STATE_STA_B);
	if (reg_val) {
		dev_err(&bus->dev, " ERROR! MDIO Read failed!\n");
		return -EBUSY;
	}


	reg_val = (u16)MDIO_GET_REG_FIELD(mdio_dev, MDIO_RDATA_REG,
					  MDIO_RDATA_DATA_M, MDIO_RDATA_DATA_S);

	return reg_val;
}
