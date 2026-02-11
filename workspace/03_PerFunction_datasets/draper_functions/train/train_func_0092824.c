exfat_flush_node(struct exfat* ef, struct exfat_node* node)
{
	cluster_t cluster;
	off_t offset;
	off_t meta1_offset, meta2_offset;
	struct exfat_entry_meta1 meta1;
	struct exfat_entry_meta2 meta2;

	if (ef->ro)
		exfat_bug("unable to flush node to read-only FS");

	if (node->parent == NULL)
		return;

	cluster = node->entry_cluster;
	offset = node->entry_offset;
	meta1_offset = co2o(ef, cluster, offset);
	next_entry(ef, node->parent, &cluster, &offset);
	meta2_offset = co2o(ef, cluster, offset);

	exfat_pread(ef->dev, &meta1, sizeof(meta1), meta1_offset);
	if (meta1.type != EXFAT_ENTRY_FILE)
		exfat_bug("invalid type of meta1: 0x%hhx", meta1.type);
	meta1.attrib = cpu_to_le16(node->flags);
	exfat_unix2exfat(node->mtime, &meta1.mdate, &meta1.mtime, &meta1.mtime_cs);
	exfat_unix2exfat(node->atime, &meta1.adate, &meta1.atime, NULL);

	exfat_pread(ef->dev, &meta2, sizeof(meta2), meta2_offset);
	if (meta2.type != EXFAT_ENTRY_FILE_INFO)
		exfat_bug("invalid type of meta2: 0x%hhx", meta2.type);
	meta2.size = meta2.real_size = cpu_to_le64(node->size);
	meta2.start_cluster = cpu_to_le32(node->start_cluster);
	meta2.flags = EXFAT_FLAG_ALWAYS1;

	if (node->size != 0 && IS_CONTIGUOUS(*node))
		meta2.flags |= EXFAT_FLAG_CONTIGUOUS;


	meta1.checksum = exfat_calc_checksum(&meta1, &meta2, node->name);

	exfat_pwrite(ef->dev, &meta1, sizeof(meta1), meta1_offset);
	exfat_pwrite(ef->dev, &meta2, sizeof(meta2), meta2_offset);

	node->flags &= ~EXFAT_ATTRIB_DIRTY;
}
