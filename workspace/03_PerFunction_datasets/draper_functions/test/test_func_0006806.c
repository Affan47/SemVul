pxa168_eth_set_mac_address(struct net_device *dev, void *addr)
{
	struct sockaddr *sa = addr;
	struct pxa168_eth_private *pep = netdev_priv(dev);
	unsigned char oldMac[ETH_ALEN];
	u32 mac_h, mac_l;

	if (!is_valid_ether_addr(sa->sa_data))
		return -EADDRNOTAVAIL;
	memcpy(oldMac, dev->dev_addr, ETH_ALEN);
	memcpy(dev->dev_addr, sa->sa_data, ETH_ALEN);

	mac_h = dev->dev_addr[0] << 24;
	mac_h |= dev->dev_addr[1] << 16;
	mac_h |= dev->dev_addr[2] << 8;
	mac_h |= dev->dev_addr[3];
	mac_l = dev->dev_addr[4] << 8;
	mac_l |= dev->dev_addr[5];
	wrl(pep, MAC_ADDR_HIGH, mac_h);
	wrl(pep, MAC_ADDR_LOW, mac_l);

	netif_addr_lock_bh(dev);
	update_hash_table_mac_address(pep, oldMac, dev->dev_addr);
	netif_addr_unlock_bh(dev);
	return 0;
}
