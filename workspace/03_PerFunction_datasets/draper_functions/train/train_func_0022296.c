cluster_save(const void *ip, const struct xt_entry_match *match)
{
	const struct xt_cluster_match_info *info = (void *)match->data;

	if (info->flags & XT_CLUSTER_F_INV)
		printf(" ! --cluster-local-nodemask 0x%08x", info->node_mask);
	else
		printf(" --cluster-local-nodemask 0x%08x", info->node_mask);

	printf(" --cluster-total-nodes %u --cluster-hash-seed 0x%08x",
		info->total_nodes, info->hash_seed);
}
