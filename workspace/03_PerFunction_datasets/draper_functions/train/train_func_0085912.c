bcmgenet_eee_enable_set(struct net_device *dev, bool enable)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	u32 off = priv->hw_params->tbuf_offset + TBUF_ENERGY_CTRL;
	u32 reg;

	if (enable && !priv->clk_eee_enabled) {
		clk_prepare_enable(priv->clk_eee);
		priv->clk_eee_enabled = true;
	}

	reg = bcmgenet_umac_readl(priv, UMAC_EEE_CTRL);
	if (enable)
		reg |= EEE_EN;
	else
		reg &= ~EEE_EN;
	bcmgenet_umac_writel(priv, reg, UMAC_EEE_CTRL);


	reg = __raw_readl(priv->base + off);
	if (enable)
		reg |= TBUF_EEE_EN | TBUF_PM_EN;
	else
		reg &= ~(TBUF_EEE_EN | TBUF_PM_EN);
	__raw_writel(reg, priv->base + off);


	reg = bcmgenet_rbuf_readl(priv, RBUF_ENERGY_CTRL);
	if (enable)
		reg |= RBUF_EEE_EN | RBUF_PM_EN;
	else
		reg &= ~(RBUF_EEE_EN | RBUF_PM_EN);
	bcmgenet_rbuf_writel(priv, reg, RBUF_ENERGY_CTRL);

	if (!enable && priv->clk_eee_enabled) {
		clk_disable_unprepare(priv->clk_eee);
		priv->clk_eee_enabled = false;
	}

	priv->eee.eee_enabled = enable;
	priv->eee.eee_active = enable;
}
