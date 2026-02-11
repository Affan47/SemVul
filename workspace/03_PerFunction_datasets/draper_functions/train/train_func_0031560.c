plip_rewrite_address(const struct net_device *dev, struct ethhdr *eth)
{
	const struct in_device *in_dev;

	rcu_read_lock();
	in_dev = __in_dev_get_rcu(dev);
	if (in_dev) {

		const struct in_ifaddr *ifa = in_dev->ifa_list;
		if (ifa) {
			memcpy(eth->h_source, dev->dev_addr, ETH_ALEN);
			memset(eth->h_dest, 0xfc, 2);
			memcpy(eth->h_dest+2, &ifa->ifa_address, 4);
		}
	}
	rcu_read_unlock();
}
