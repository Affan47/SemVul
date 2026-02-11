bond_tlb_xmit(struct sk_buff *skb, struct net_device *bond_dev)
{
	struct bonding *bond = netdev_priv(bond_dev);
	struct ethhdr *eth_data;
	struct slave *tx_slave = NULL;
	u32 hash_index;

	skb_reset_mac_header(skb);
	eth_data = eth_hdr(skb);


	if (!is_multicast_ether_addr(eth_data->h_dest)) {
		switch (skb->protocol) {
		case htons(ETH_P_IP):
		case htons(ETH_P_IPX):

		case htons(ETH_P_IPV6):
			hash_index = bond_xmit_hash(bond, skb);
			if (bond->params.tlb_dynamic_lb) {
				tx_slave = tlb_choose_channel(bond,
							      hash_index & 0xFF,
							      skb->len);
			} else {
				struct bond_up_slave *slaves;
				unsigned int count;

				slaves = rcu_dereference(bond->slave_arr);
				count = slaves ? ACCESS_ONCE(slaves->count) : 0;
				if (likely(count))
					tx_slave = slaves->arr[hash_index %
							       count];
			}
			break;
		}
	}
	return bond_do_alb_xmit(skb, bond, tx_slave);
}
