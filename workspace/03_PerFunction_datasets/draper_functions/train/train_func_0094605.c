xenvif_mcast_add(struct xenvif *vif, const u8 *addr)
{
	struct xenvif_mcast_addr *mcast;

	if (vif->fe_mcast_count == XEN_NETBK_MCAST_MAX) {
		if (net_ratelimit())
			netdev_err(vif->dev,
				   "Too many multicast addresses\n");
		return -ENOSPC;
	}

	mcast = kzalloc(sizeof(*mcast), GFP_ATOMIC);
	if (!mcast)
		return -ENOMEM;

	ether_addr_copy(mcast->addr, addr);
	list_add_tail_rcu(&mcast->entry, &vif->fe_mcast_addr);
	vif->fe_mcast_count++;

	return 0;
}
