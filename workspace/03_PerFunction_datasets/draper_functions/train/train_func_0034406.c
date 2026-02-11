geneve_sock_add(struct geneve_dev *geneve, bool ipv6)
{
	struct net *net = geneve->net;
	struct geneve_net *gn = net_generic(net, geneve_net_id);
	struct geneve_sock *gs;
	__u32 hash;

	gs = geneve_find_sock(gn, ipv6 ? AF_INET6 : AF_INET, geneve->dst_port);
	if (gs) {
		gs->refcnt++;
		goto out;
	}

	gs = geneve_socket_create(net, geneve->dst_port, ipv6, geneve->flags);
	if (IS_ERR(gs))
		return PTR_ERR(gs);

out:
	gs->collect_md = geneve->collect_md;
	gs->flags = geneve->flags;
#if IS_ENABLED(CONFIG_IPV6)
	if (ipv6)
		geneve->sock6 = gs;
	else
#endif
		geneve->sock4 = gs;

	hash = geneve_net_vni_hash(geneve->vni);
	hlist_add_head_rcu(&geneve->hlist, &gs->vni_list[hash]);
	return 0;
}
