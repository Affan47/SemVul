next_entry(struct exfat* ef, const struct exfat_node* parent,
		cluster_t* cluster, off_t* offset)
{
	*offset += sizeof(struct exfat_entry);
	if (*offset % CLUSTER_SIZE(*ef->sb) == 0)

		*cluster = exfat_next_cluster(ef, parent, *cluster);
}
