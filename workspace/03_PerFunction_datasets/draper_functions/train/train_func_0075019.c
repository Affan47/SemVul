truncate_hole(struct inode *inode, pgoff_t pg_start, pgoff_t pg_end)
{
	int err;

	while (pg_start < pg_end) {
		struct dnode_of_data dn;
		pgoff_t end_offset, count;

		set_new_dnode(&dn, inode, NULL, NULL, 0);
		err = get_dnode_of_data(&dn, pg_start, LOOKUP_NODE);
		if (err) {
			if (err == -ENOENT) {
				pg_start++;
				continue;
			}
			return err;
		}

		end_offset = ADDRS_PER_PAGE(dn.node_page, F2FS_I(inode));
		count = min(end_offset - dn.ofs_in_node, pg_end - pg_start);

		f2fs_bug_on(F2FS_I_SB(inode), count == 0 || count > end_offset);

		truncate_data_blocks_range(&dn, count);
		f2fs_put_dnode(&dn);

		pg_start += count;
	}
	return 0;
}
