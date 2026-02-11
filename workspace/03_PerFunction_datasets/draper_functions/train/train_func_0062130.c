exfat_advance_cluster(const struct exfat* ef,
		struct exfat_node* node, uint32_t count)
{
	uint32_t i;

	if (node->fptr_index > count)
	{
		node->fptr_index = 0;
		node->fptr_cluster = node->start_cluster;
	}

	for (i = node->fptr_index; i < count; i++)
	{
		node->fptr_cluster = exfat_next_cluster(ef, node, node->fptr_cluster);
		if (CLUSTER_INVALID(node->fptr_cluster))
			break;

	}
	node->fptr_index = count;
	return node->fptr_cluster;
}
