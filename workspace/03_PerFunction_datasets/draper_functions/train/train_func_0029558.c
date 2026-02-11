xgmac_get_wol(struct net_device *dev,
			       struct ethtool_wolinfo *wol)
{
	struct xgmac_priv *priv = netdev_priv(dev);

	if (device_can_wakeup(priv->device)) {
		wol->supported = WAKE_MAGIC | WAKE_UCAST;
		wol->wolopts = priv->wolopts;
	}
}
