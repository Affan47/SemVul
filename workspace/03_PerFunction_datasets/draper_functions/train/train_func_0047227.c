umac_enable_set(struct bcm_sysport_priv *priv,
				   u32 mask, unsigned int enable)
{
	u32 reg;

	reg = umac_readl(priv, UMAC_CMD);
	if (enable)
		reg |= mask;
	else
		reg &= ~mask;
	umac_writel(priv, reg, UMAC_CMD);


	if (enable == 0)
		usleep_range(1000, 2000);
}
