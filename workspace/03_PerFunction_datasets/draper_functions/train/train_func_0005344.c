set_addr_filters(const struct net_device *dev, bool sleep)
{
	u64 mhash = 0;
	u64 uhash = 0;
	bool free = true;
	unsigned int offset, naddr;
	const u8 *addr[7];
	int ret;
	const struct port_info *pi = netdev_priv(dev);


	for (offset = 0; ; offset += naddr) {
		naddr = collect_netdev_uc_list_addrs(dev, addr, offset,
						     ARRAY_SIZE(addr));
		if (naddr == 0)
			break;

		ret = t4vf_alloc_mac_filt(pi->adapter, pi->viid, free,
					  naddr, addr, NULL, &uhash, sleep);
		if (ret < 0)
			return ret;

		free = false;
	}


	for (offset = 0; ; offset += naddr) {
		naddr = collect_netdev_mc_list_addrs(dev, addr, offset,
						     ARRAY_SIZE(addr));
		if (naddr == 0)
			break;

		ret = t4vf_alloc_mac_filt(pi->adapter, pi->viid, free,
					  naddr, addr, NULL, &mhash, sleep);
		if (ret < 0)
			return ret;
		free = false;
	}

	return t4vf_set_addr_hash(pi->adapter, pi->viid, uhash != 0,
				  uhash | mhash, sleep);
}
