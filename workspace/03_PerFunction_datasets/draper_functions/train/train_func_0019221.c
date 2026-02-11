r871x_net_set_mac_address(struct net_device *pnetdev, void *p)
{
	struct _adapter *padapter = netdev_priv(pnetdev);
	struct sockaddr *addr = p;

	if (!padapter->bup)
		ether_addr_copy(pnetdev->dev_addr, addr->sa_data);
	return 0;
}
