bcm_sysport_change_mac(struct net_device *dev, void *p)
{
	struct bcm_sysport_priv *priv = netdev_priv(dev);
	struct sockaddr *addr = p;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EINVAL;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);


	if (!netif_running(dev))
		return 0;

	umac_set_hw_addr(priv, dev->dev_addr);

	return 0;
}
