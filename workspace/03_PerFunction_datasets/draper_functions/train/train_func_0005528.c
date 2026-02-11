find_index(struct inode *ip, u32 index,
					 struct metapage ** mp, s64 *lblock)
{
	struct jfs_inode_info *jfs_ip = JFS_IP(ip);
	s64 blkno;
	s64 offset;
	int page_offset;
	struct dir_table_slot *slot;
	static int maxWarnings = 10;

	if (index < 2) {
		if (maxWarnings) {
			jfs_warn("find_entry called with index = %d", index);
			maxWarnings--;
		}
		return NULL;
	}

	if (index >= jfs_ip->next_index) {
		jfs_warn("find_entry called with index >= next_index");
		return NULL;
	}

	if (jfs_dirtable_inline(ip)) {


		*mp = NULL;
		slot = &jfs_ip->i_dirtable[index - 2];
	} else {
		offset = (index - 2) * sizeof(struct dir_table_slot);
		page_offset = offset & (PSIZE - 1);
		blkno = ((offset + 1) >> L2PSIZE) <<
		    JFS_SBI(ip->i_sb)->l2nbperpage;

		if (*mp && (*lblock != blkno)) {
			release_metapage(*mp);
			*mp = NULL;
		}
		if (!(*mp)) {
			*lblock = blkno;
			*mp = read_index_page(ip, blkno);
		}
		if (!(*mp)) {
			jfs_err("free_index: error reading directory table");
			return NULL;
		}

		slot =
		    (struct dir_table_slot *) ((char *) (*mp)->data +
					       page_offset);
	}
	return slot;
}
