bcm_sf2_eee_enable_set(struct dsa_switch *ds, int port, bool enable)
{
	struct bcm_sf2_priv *priv = ds_to_priv(ds);
	u32 reg;

	reg = core_readl(priv, CORE_EEE_EN_CTRL);
	if (enable)
		reg |= 1 << port;
	else
		reg &= ~(1 << port);
	core_writel(priv, reg, CORE_EEE_EN_CTRL);
}
