dlci_open(struct net_device *dev)
{
	struct dlci_local	*dlp;
	struct frad_local	*flp;
	int			err;

	dlp = netdev_priv(dev);

	if (!*(short *)(dev->dev_addr))
		return -EINVAL;

	if (!netif_running(dlp->slave))
		return -ENOTCONN;

	flp = netdev_priv(dlp->slave);
	err = (*flp->activate)(dlp->slave, dev);
	if (err)
		return err;

	netif_start_queue(dev);

	return 0;
}
