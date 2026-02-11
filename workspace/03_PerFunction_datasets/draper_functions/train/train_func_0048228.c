erase_entry(struct exfat* ef, struct exfat_node* node)
{
	cluster_t cluster = node->entry_cluster;
	off_t offset = node->entry_offset;
	int name_entries = DIV_ROUND_UP(utf16_length(node->name), EXFAT_ENAME_MAX);
	uint8_t entry_type;

	entry_type = EXFAT_ENTRY_FILE & ~EXFAT_ENTRY_VALID;
	exfat_pwrite(ef->dev, &entry_type, 1, co2o(ef, cluster, offset));

	next_entry(ef, node->parent, &cluster, &offset);
	entry_type = EXFAT_ENTRY_FILE_INFO & ~EXFAT_ENTRY_VALID;
	exfat_pwrite(ef->dev, &entry_type, 1, co2o(ef, cluster, offset));

	while (name_entries--)
	{
		next_entry(ef, node->parent, &cluster, &offset);
		entry_type = EXFAT_ENTRY_FILE_NAME & ~EXFAT_ENTRY_VALID;
		exfat_pwrite(ef->dev, &entry_type, 1, co2o(ef, cluster, offset));
	}
}
