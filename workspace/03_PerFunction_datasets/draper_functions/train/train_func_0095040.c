ipoib_get_iflink(const struct net_device *dev)
{
	struct ipoib_dev_priv *priv = netdev_priv(dev);


	if (!test_bit(IPOIB_FLAG_SUBINTERFACE, &priv->flags))
		return dev->ifindex;


	return priv->parent->ifindex;
}
