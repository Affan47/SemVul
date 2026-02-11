ipvlan_add_addr6(struct ipvl_dev *ipvlan, struct in6_addr *ip6_addr)
{
	struct ipvl_addr *addr;

	if (ipvlan_addr_busy(ipvlan->port, ip6_addr, true)) {
		netif_err(ipvlan, ifup, ipvlan->dev,
			  "Failed to add IPv6=%pI6c addr for %s intf\n",
			  ip6_addr, ipvlan->dev->name);
		return -EINVAL;
	}
	addr = kzalloc(sizeof(struct ipvl_addr), GFP_ATOMIC);
	if (!addr)
		return -ENOMEM;

	addr->master = ipvlan;
	memcpy(&addr->ip6addr, ip6_addr, sizeof(struct in6_addr));
	addr->atype = IPVL_IPV6;
	list_add_tail(&addr->anode, &ipvlan->addrs);


	if (netif_running(ipvlan->dev))
		ipvlan_ht_addr_add(ipvlan, addr);

	return 0;
}
