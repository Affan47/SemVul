rpc_call_prepare(
	enum dht_rpc_op op, knode_t *kn, int delay, uint32 flags,
	dht_rpc_cb_t cb, void *arg)
{
	int i;
	struct rpc_cb *rcb;
	struct guid muid;

	knode_check(kn);


	for (i = 0; i < 100; i++) {
		guid_random_muid(&muid);

		if (!hikset_contains(pending, &muid))
			break;
	}

	if G_UNLIKELY(100 == i)
		g_error("bad luck with random number generator");


	WALLOC0(rcb);
	rcb->magic = RPC_CB_MAGIC;
	rcb->op = op;
	rcb->kn = knode_refcnt_inc(kn);
	rcb->flags = flags;
	rcb->muid = atom_guid_get(&muid);
	rcb->addr = kn->addr;
	rcb->port = kn->port;
	rcb->timeout = cq_main_insert(delay, rpc_timed_out, rcb);
	rcb->cb = cb;
	rcb->arg = arg;
	tm_now_exact(&rcb->start);
	knode_rpc_inc(kn);

	hikset_insert_key(pending, &rcb->muid);
	gnet_stats_inc_general(GNR_DHT_RPC_MSG_PREPARED);

	if (GNET_PROPERTY(dht_rpc_debug) > 4) {
		g_debug("DHT RPC created %s #%s to %s with callback %s(%p), "
			"timeout %d ms",
			op_to_string(rcb->op), guid_to_string(rcb->muid),
			knode_to_string(kn), stacktrace_function_name(cb), arg, delay);
	}

	return rcb->muid;
}
