encx24j600_check_link_status(struct encx24j600_priv *priv)
{
	struct net_device *dev = priv->ndev;
	u16 estat;

	estat = encx24j600_read_reg(priv, ESTAT);

	if (estat & PHYLNK) {
		if (priv->autoneg == AUTONEG_ENABLE)
			encx24j600_wait_for_autoneg(priv);

		netif_carrier_on(dev);
		netif_info(priv, ifup, dev, "link up\n");
	} else {
		netif_info(priv, ifdown, dev, "link down\n");


		priv->autoneg  = AUTONEG_ENABLE;
		priv->full_duplex = true;
		priv->speed = SPEED_100;
		netif_carrier_off(dev);
	}
}
