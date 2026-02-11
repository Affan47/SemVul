bcmgenet_set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	struct bcmgenet_priv *priv = netdev_priv(dev);
	struct device *kdev = &priv->pdev->dev;
	u32 reg;

	if (!device_can_wakeup(kdev))
		return -ENOTSUPP;

	if (wol->wolopts & ~(WAKE_MAGIC | WAKE_MAGICSECURE))
		return -EINVAL;

	reg = bcmgenet_umac_readl(priv, UMAC_MPD_CTRL);
	if (wol->wolopts & WAKE_MAGICSECURE) {
		bcmgenet_umac_writel(priv, get_unaligned_be16(&wol->sopass[0]),
				     UMAC_MPD_PW_MS);
		bcmgenet_umac_writel(priv, get_unaligned_be32(&wol->sopass[2]),
				     UMAC_MPD_PW_LS);
		reg |= MPD_PW_EN;
	} else {
		reg &= ~MPD_PW_EN;
	}
	bcmgenet_umac_writel(priv, reg, UMAC_MPD_CTRL);


	if (wol->wolopts) {
		device_set_wakeup_enable(kdev, 1);

		if (priv->wol_irq_disabled)
			enable_irq_wake(priv->wol_irq);
		priv->wol_irq_disabled = false;
	} else {
		device_set_wakeup_enable(kdev, 0);

		if (!priv->wol_irq_disabled)
			disable_irq_wake(priv->wol_irq);
		priv->wol_irq_disabled = true;
	}

	priv->wolopts = wol->wolopts;

	return 0;
}
