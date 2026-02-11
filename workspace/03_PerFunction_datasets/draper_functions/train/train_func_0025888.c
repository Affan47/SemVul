dwceqos_set_mac_address(struct net_device *ndev, void *addr)
{
	struct net_local *lp = netdev_priv(ndev);
	struct sockaddr *hwaddr = (struct sockaddr *)addr;

	if (netif_running(ndev))
		return -EBUSY;

	if (!is_valid_ether_addr(hwaddr->sa_data))
		return -EADDRNOTAVAIL;

	memcpy(ndev->dev_addr, hwaddr->sa_data, ndev->addr_len);

	dwceqos_set_umac_addr(lp, lp->ndev->dev_addr, 0);
	return 0;
}
