dht_verify_node(knode_t *kn, knode_t *new, bool alive)
{
	struct addr_verify *av;

	knode_check(kn);
	knode_check(new);
	g_assert(new->status == KNODE_UNKNOWN);
	g_assert(!(kn->flags & KNODE_F_VERIFYING));

	WALLOC0(av);

	if (GNET_PROPERTY(dht_debug))
		g_debug("DHT node %s was at %s, now %s -- verifying",
			kuid_to_hex_string(kn->id),
			host_addr_port_to_string(kn->addr, kn->port),
			host_addr_port_to_string2(new->addr, new->port));

	kn->flags |= KNODE_F_VERIFYING;
	av->old = knode_refcnt_inc(kn);
	av->new = knode_refcnt_inc(new);
	av->new_is_alive = booleanize(alive);

	gnet_stats_inc_general(GNR_DHT_NODE_VERIFICATIONS);


	dht_rpc_ping_extended(kn, RPC_CALL_NO_VERIFY, dht_addr_verify_cb, av);
}
