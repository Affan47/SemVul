ipvlan_xmit_mode_l3(struct sk_buff *skb, struct net_device *dev)
{
	const struct ipvl_dev *ipvlan = netdev_priv(dev);
	void *lyr3h;
	struct ipvl_addr *addr;
	int addr_type;

	lyr3h = ipvlan_get_L3_hdr(skb, &addr_type);
	if (!lyr3h)
		goto out;

	addr = ipvlan_addr_lookup(ipvlan->port, lyr3h, addr_type, true);
	if (addr)
		return ipvlan_rcv_frame(addr, &skb, true);

out:
	skb->dev = ipvlan->phy_dev;
	return ipvlan_process_outbound(skb, ipvlan);
}
