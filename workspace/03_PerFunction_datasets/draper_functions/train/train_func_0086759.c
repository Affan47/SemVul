encx24j600_setlink(struct net_device *dev, u8 autoneg, u16 speed,
			      u8 duplex)
{
	struct encx24j600_priv *priv = netdev_priv(dev);
	int ret = 0;

	if (!priv->hw_enabled) {


		if (speed == SPEED_10 || speed == SPEED_100) {
			priv->autoneg = (autoneg == AUTONEG_ENABLE);
			priv->full_duplex = (duplex == DUPLEX_FULL);
			priv->speed = (speed == SPEED_100);
		} else {
			netif_warn(priv, link, dev, "unsupported link speed setting\n");


			ret = -EOPNOTSUPP;
		}
	} else {
		netif_warn(priv, link, dev, "Warning: hw must be disabled to set link mode\n");
		ret = -EBUSY;
	}
	return ret;
}
