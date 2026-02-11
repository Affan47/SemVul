stmmac_mdio_read(struct mii_bus *bus, int phyaddr, int phyreg)
{
	struct net_device *ndev = bus->priv;
	struct stmmac_priv *priv = netdev_priv(ndev);
	unsigned int mii_address = priv->hw->mii.addr;
	unsigned int mii_data = priv->hw->mii.data;

	int data;
	u16 regValue = (((phyaddr << 11) & (0x0000F800)) |
			((phyreg << 6) & (0x000007C0)));
	regValue |= MII_BUSY | ((priv->clk_csr & 0xF) << 2);

	if (stmmac_mdio_busy_wait(priv->ioaddr, mii_address))
		return -EBUSY;

	writel(regValue, priv->ioaddr + mii_address);

	if (stmmac_mdio_busy_wait(priv->ioaddr, mii_address))
		return -EBUSY;


	data = (int)readl(priv->ioaddr + mii_data);

	return data;
}
