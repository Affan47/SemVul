hix5hd2_mdio_write(struct mii_bus *bus, int phy, int reg, u16 val)
{
	struct hix5hd2_priv *priv = bus->priv;
	void __iomem *base = priv->base;
	int ret;

	ret = hix5hd2_mdio_wait_ready(bus);
	if (ret < 0)
		goto out;

	writel_relaxed(val, base + MDIO_SINGLE_DATA);
	writel_relaxed(MDIO_WRITE | phy << 8 | reg, base + MDIO_SINGLE_CMD);
	ret = hix5hd2_mdio_wait_ready(bus);
out:
	return ret;
}
