set_rx_mode(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);
	long ioaddr = dev->base_addr;

	if (!netdev_mc_empty(dev) || (dev->flags & (IFF_ALLMULTI|IFF_PROMISC)))
		lp->addr_mode = CMR2h_PROMISC;
	else
		lp->addr_mode = CMR2h_Normal;
	write_reg_high(ioaddr, CMR2, lp->addr_mode);
}
