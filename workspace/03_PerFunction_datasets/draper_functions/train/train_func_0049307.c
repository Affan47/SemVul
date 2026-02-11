forget_node(knode_t *kn)
{
	knode_check(kn);
	g_assert(kn->status != KNODE_UNKNOWN);
	g_assert(kn->refcnt > 0);

	list_update_stats(kn->status, -1);
	kn->flags &= ~KNODE_F_ALIVE;
	kn->status = KNODE_UNKNOWN;
	knode_free(kn);

	gnet_stats_inc_general(GNR_DHT_ROUTING_EVICTED_NODES);
}
