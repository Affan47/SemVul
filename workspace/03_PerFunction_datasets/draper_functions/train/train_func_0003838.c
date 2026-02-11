cxgb4vf_set_mac_addr(struct net_device *dev, void *_addr)
{
	int ret;
	struct sockaddr *addr = _addr;
	struct port_info *pi = netdev_priv(dev);

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	ret = t4vf_change_mac(pi->adapter, pi->viid, pi->xact_addr_filt,
			      addr->sa_data, true);
	if (ret < 0)
		return ret;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);
	pi->xact_addr_filt = ret;
	return 0;
}
