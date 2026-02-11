dht_remove_timeouting_node(knode_t *kn)
{
	struct kbucket *kb;

	kb = dht_find_bucket(kn->id);

	if (!hikset_contains(kb->nodes->all, kn->id))
		return;

	dht_set_node_status(kn, KNODE_STALE);


	STATIC_ASSERT(KNODE_MAX_TIMEOUTS > 0);

	if (hash_list_length(kb->nodes->good) >= K_BUCKET_GOOD)
		dht_remove_node_from_bucket(kn, kb);
	else
		kn->rpc_timeouts = KNODE_MAX_TIMEOUTS;
}
