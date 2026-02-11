umac_enable_set(struct bcmgenet_priv *priv, u32 mask, bool enable)
{
	u32 reg;

	reg = bcmgenet_umac_readl(priv, UMAC_CMD);
	if (enable)
		reg |= mask;
	else
		reg &= ~mask;
	bcmgenet_umac_writel(priv, reg, UMAC_CMD);


	if (enable == 0)
		usleep_range(1000, 2000);
}
