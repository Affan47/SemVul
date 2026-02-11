init_realtek_8211c(struct net_device *dev, struct fe_priv *np)
{
	u32 reg;
	u8 __iomem *base = get_hwbase(dev);
	u32 powerstate = readl(base + NvRegPowerState2);


	powerstate |= NVREG_POWERSTATE2_PHY_RESET;
	writel(powerstate, base + NvRegPowerState2);
	msleep(25);

	powerstate &= ~NVREG_POWERSTATE2_PHY_RESET;
	writel(powerstate, base + NvRegPowerState2);
	msleep(25);

	reg = mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG6, MII_READ);
	reg |= PHY_REALTEK_INIT9;
	if (mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG6, reg))
		return PHY_ERROR;
	if (mii_rw(dev, np->phyaddr,
		   PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT10))
		return PHY_ERROR;
	reg = mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG7, MII_READ);
	if (!(reg & PHY_REALTEK_INIT11)) {
		reg |= PHY_REALTEK_INIT11;
		if (mii_rw(dev, np->phyaddr, PHY_REALTEK_INIT_REG7, reg))
			return PHY_ERROR;
	}
	if (mii_rw(dev, np->phyaddr,
		   PHY_REALTEK_INIT_REG1, PHY_REALTEK_INIT1))
		return PHY_ERROR;

	return 0;
}
