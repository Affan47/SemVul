htbl_key_search(struct hlist_head *h,
						  struct flow_keys *k)
{
	struct enic_rfs_fltr_node *tpos;

	hlist_for_each_entry(tpos, h, node)
		if (tpos->keys.addrs.v4addrs.src == k->addrs.v4addrs.src &&
		    tpos->keys.addrs.v4addrs.dst == k->addrs.v4addrs.dst &&
		    tpos->keys.ports.ports == k->ports.ports &&
		    tpos->keys.basic.ip_proto == k->basic.ip_proto &&
		    tpos->keys.basic.n_proto == k->basic.n_proto)
			return tpos;
	return NULL;
}
