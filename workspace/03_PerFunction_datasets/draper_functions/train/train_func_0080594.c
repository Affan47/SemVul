tc589_probe(struct pcmcia_device *link)
{
	struct el3_private *lp;
	struct net_device *dev;

	dev_dbg(&link->dev, "3c589_attach()\n");


	dev = alloc_etherdev(sizeof(struct el3_private));
	if (!dev)
		return -ENOMEM;
	lp = netdev_priv(dev);
	link->priv = dev;
	lp->p_dev = link;

	spin_lock_init(&lp->lock);
	link->resource[0]->end = 16;
	link->resource[0]->flags |= IO_DATA_PATH_WIDTH_16;

	link->config_flags |= CONF_ENABLE_IRQ;
	link->config_index = 1;

	dev->netdev_ops = &el3_netdev_ops;
	dev->watchdog_timeo = TX_TIMEOUT;

	dev->ethtool_ops = &netdev_ethtool_ops;

	return tc589_config(link);
}
