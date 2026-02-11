exfat_generic_pread(const struct exfat* ef, struct exfat_node* node,
		void* buffer, size_t size, off_t offset)
{
	cluster_t cluster;
	char* bufp = buffer;
	off_t lsize, loffset, remainder;

	if (offset >= node->size)
		return 0;
	if (size == 0)
		return 0;

	cluster = exfat_advance_cluster(ef, node, offset / CLUSTER_SIZE(*ef->sb));
	if (CLUSTER_INVALID(cluster))
	{
		exfat_error("invalid cluster 0x%x while reading", cluster);
		return -1;
	}

	loffset = offset % CLUSTER_SIZE(*ef->sb);
	remainder = MIN(size, node->size - offset);
	while (remainder > 0)
	{
		if (CLUSTER_INVALID(cluster))
		{
			exfat_error("invalid cluster 0x%x while reading", cluster);
			return -1;
		}
		lsize = MIN(CLUSTER_SIZE(*ef->sb) - loffset, remainder);
		exfat_pread(ef->dev, bufp, lsize, exfat_c2o(ef, cluster) + loffset);
		bufp += lsize;
		loffset = 0;
		remainder -= lsize;
		cluster = exfat_next_cluster(ef, node, cluster);
	}
	if (!ef->ro && !ef->noatime)
		exfat_update_atime(node);
	return MIN(size, node->size - offset) - remainder;
}
