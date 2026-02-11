truncate_data_blocks_range(struct dnode_of_data *dn, int count)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(dn->inode);
	struct f2fs_node *raw_node;
	int nr_free = 0, ofs = dn->ofs_in_node, len = count;
	__le32 *addr;

	raw_node = F2FS_NODE(dn->node_page);
	addr = blkaddr_in_node(raw_node) + ofs;

	for (; count > 0; count--, addr++, dn->ofs_in_node++) {
		block_t blkaddr = le32_to_cpu(*addr);
		if (blkaddr == NULL_ADDR)
			continue;

		dn->data_blkaddr = NULL_ADDR;
		set_data_blkaddr(dn);
		invalidate_blocks(sbi, blkaddr);
		if (dn->ofs_in_node == 0 && IS_INODE(dn->node_page))
			clear_inode_flag(F2FS_I(dn->inode),
						FI_FIRST_BLOCK_WRITTEN);
		nr_free++;
	}

	if (nr_free) {
		pgoff_t fofs;


		fofs = start_bidx_of_node(ofs_of_node(dn->node_page),
						F2FS_I(dn->inode)) + ofs;
		f2fs_update_extent_cache_range(dn, fofs, 0, len);
		dec_valid_block_count(sbi, dn->inode, nr_free);
		set_page_dirty(dn->node_page);
		sync_inode_page(dn);
	}
	dn->ofs_in_node = ofs;

	trace_f2fs_truncate_data_blocks_range(dn->inode, dn->nid,
					 dn->ofs_in_node, nr_free);
	return nr_free;
}
