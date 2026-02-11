bond_xmit_hash(struct bonding *bond, struct sk_buff *skb)
{
	struct flow_keys flow;
	u32 hash;

	if (bond->params.xmit_policy == BOND_XMIT_POLICY_ENCAP34 &&
	    skb->l4_hash)
		return skb->hash;

	if (bond->params.xmit_policy == BOND_XMIT_POLICY_LAYER2 ||
	    !bond_flow_dissect(bond, skb, &flow))
		return bond_eth_hash(skb);

	if (bond->params.xmit_policy == BOND_XMIT_POLICY_LAYER23 ||
	    bond->params.xmit_policy == BOND_XMIT_POLICY_ENCAP23)
		hash = bond_eth_hash(skb);
	else
		hash = (__force u32)flow.ports.ports;
	hash ^= (__force u32)flow_get_u32_dst(&flow) ^
		(__force u32)flow_get_u32_src(&flow);
	hash ^= (hash >> 16);
	hash ^= (hash >> 8);

	return hash >> 1;
}
