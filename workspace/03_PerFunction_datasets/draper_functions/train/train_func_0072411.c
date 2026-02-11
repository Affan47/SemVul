orion_mdio_write(struct mii_bus *bus, int mii_id,
			    int regnum, u16 value)
{
	struct orion_mdio_dev *dev = bus->priv;
	int ret;

	mutex_lock(&dev->lock);

	ret = orion_mdio_wait_ready(bus);
	if (ret < 0)
		goto out;

	writel(((mii_id << MVMDIO_SMI_PHY_ADDR_SHIFT) |
		(regnum << MVMDIO_SMI_PHY_REG_SHIFT)  |
		MVMDIO_SMI_WRITE_OPERATION            |
		(value << MVMDIO_SMI_DATA_SHIFT)),
	       dev->regs);

out:
	mutex_unlock(&dev->lock);
	return ret;
}
