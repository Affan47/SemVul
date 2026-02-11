nb8800_nway_reset(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);

	if (!priv->phydev)
		return -ENODEV;

	return genphy_restart_aneg(priv->phydev);
}
