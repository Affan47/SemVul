find_one_address (struct nl_object *object, void *user_data)
{
	FindAddrInfo *info = user_data;
	struct rtnl_addr *addr = (struct rtnl_addr *) object;
	struct nl_addr *local;
	void *binaddr;

	if (info->found)
		return;

	if (rtnl_addr_get_ifindex (addr) != info->ifindex)
		return;
	if (rtnl_addr_get_family (addr) != info->family)
		return;

	if (rtnl_addr_get_prefixlen (addr) != info->prefix)
		return;

	local = rtnl_addr_get_local (addr);
	if (nl_addr_get_family (local) != info->family)
		return;
	if (nl_addr_get_len (local) != info->addrlen)
		return;
	binaddr = nl_addr_get_binary_addr (local);
	if (binaddr) {
		if (memcmp (binaddr, info->addr, info->addrlen) == 0)
			info->found = TRUE;
	}
}
