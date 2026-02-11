geneve_gro_complete(struct sk_buff *skb, int nhoff,
			       struct udp_offload *uoff)
{
	struct genevehdr *gh;
	struct packet_offload *ptype;
	__be16 type;
	int gh_len;
	int err = -ENOSYS;

	udp_tunnel_gro_complete(skb, nhoff);

	gh = (struct genevehdr *)(skb->data + nhoff);
	gh_len = geneve_hlen(gh);
	type = gh->proto_type;

	rcu_read_lock();
	ptype = gro_find_complete_by_type(type);
	if (ptype)
		err = ptype->callbacks.gro_complete(skb, nhoff + gh_len);

	rcu_read_unlock();
	return err;
}
