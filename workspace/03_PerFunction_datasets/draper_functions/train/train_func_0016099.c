gem_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *macaddr = (struct sockaddr *) addr;
	struct gem *gp = netdev_priv(dev);
	unsigned char *e = &dev->dev_addr[0];

	if (!is_valid_ether_addr(macaddr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(dev->dev_addr, macaddr->sa_data, dev->addr_len);


	if (!netif_running(dev) || !netif_device_present(dev))
		return 0;


	if (WARN_ON(!gp->cell_enabled))
		return 0;

	writel((e[4] << 8) | e[5], gp->regs + MAC_ADDR0);
	writel((e[2] << 8) | e[3], gp->regs + MAC_ADDR1);
	writel((e[0] << 8) | e[1], gp->regs + MAC_ADDR2);

	return 0;
}
