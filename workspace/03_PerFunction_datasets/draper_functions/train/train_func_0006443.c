process_rpc_calls(struct era *era)
{
	int r;
	bool need_commit = false;
	struct list_head calls;
	struct rpc *rpc, *tmp;

	INIT_LIST_HEAD(&calls);
	spin_lock(&era->rpc_lock);
	list_splice_init(&era->rpc_calls, &calls);
	spin_unlock(&era->rpc_lock);

	list_for_each_entry_safe(rpc, tmp, &calls, list) {
		rpc->result = rpc->fn0 ? rpc->fn0(era->md) : rpc->fn1(era->md, rpc->arg);
		need_commit = true;
	}

	if (need_commit) {
		r = metadata_commit(era->md);
		if (r)
			list_for_each_entry_safe(rpc, tmp, &calls, list)
				rpc->result = r;
	}

	list_for_each_entry_safe(rpc, tmp, &calls, list)
		complete(&rpc->complete);
}
