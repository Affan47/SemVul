collect_netdev_uc_list_addrs(const struct net_device *dev,
							const u8 **addr,
							unsigned int offset,
							unsigned int maxaddrs)
{
	unsigned int index = 0;
	unsigned int naddr = 0;
	const struct netdev_hw_addr *ha;

	for_each_dev_addr(dev, ha)
		if (index++ >= offset) {
			addr[naddr++] = ha->addr;
			if (naddr >= maxaddrs)
				break;
		}
	return naddr;
}
