enic_set_mac_addr(struct net_device *netdev, char *addr)
{
	struct enic *enic = netdev_priv(netdev);

	if (enic_is_dynamic(enic) || enic_is_sriov_vf(enic)) {
		if (!is_valid_ether_addr(addr) && !is_zero_ether_addr(addr))
			return -EADDRNOTAVAIL;
	} else {
		if (!is_valid_ether_addr(addr))
			return -EADDRNOTAVAIL;
	}

	memcpy(netdev->dev_addr, addr, netdev->addr_len);

	return 0;
}
