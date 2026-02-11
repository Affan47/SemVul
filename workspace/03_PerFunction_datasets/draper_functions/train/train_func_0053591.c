hfsplus_file_truncate(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;
	struct hfsplus_inode_info *hip = HFSPLUS_I(inode);
	struct hfs_find_data fd;
	u32 alloc_cnt, blk_cnt, start;
	int res;

	hfs_dbg(INODE, "truncate: %lu, %llu -> %llu\n",
		inode->i_ino, (long long)hip->phys_size, inode->i_size);

	if (inode->i_size > hip->phys_size) {
		struct address_space *mapping = inode->i_mapping;
		struct page *page;
		void *fsdata;
		loff_t size = inode->i_size;

		res = pagecache_write_begin(NULL, mapping, size, 0,
						AOP_FLAG_UNINTERRUPTIBLE,
						&page, &fsdata);
		if (res)
			return;
		res = pagecache_write_end(NULL, mapping, size,
			0, 0, page, fsdata);
		if (res < 0)
			return;
		mark_inode_dirty(inode);
		return;
	} else if (inode->i_size == hip->phys_size)
		return;

	blk_cnt = (inode->i_size + HFSPLUS_SB(sb)->alloc_blksz - 1) >>
			HFSPLUS_SB(sb)->alloc_blksz_shift;

	mutex_lock(&hip->extents_lock);

	alloc_cnt = hip->alloc_blocks;
	if (blk_cnt == alloc_cnt)
		goto out_unlock;

	res = hfs_find_init(HFSPLUS_SB(sb)->ext_tree, &fd);
	if (res) {
		mutex_unlock(&hip->extents_lock);

		return;
	}
	while (1) {
		if (alloc_cnt == hip->first_blocks) {
			hfsplus_free_extents(sb, hip->first_extents,
					     alloc_cnt, alloc_cnt - blk_cnt);
			hfsplus_dump_extent(hip->first_extents);
			hip->first_blocks = blk_cnt;
			break;
		}
		res = __hfsplus_ext_cache_extent(&fd, inode, alloc_cnt);
		if (res)
			break;
		start = hip->cached_start;
		hfsplus_free_extents(sb, hip->cached_extents,
				     alloc_cnt - start, alloc_cnt - blk_cnt);
		hfsplus_dump_extent(hip->cached_extents);
		if (blk_cnt > start) {
			hip->extent_state |= HFSPLUS_EXT_DIRTY;
			break;
		}
		alloc_cnt = start;
		hip->cached_start = hip->cached_blocks = 0;
		hip->extent_state &= ~(HFSPLUS_EXT_DIRTY | HFSPLUS_EXT_NEW);
		hfs_brec_remove(&fd);
	}
	hfs_find_exit(&fd);

	hip->alloc_blocks = blk_cnt;
out_unlock:
	mutex_unlock(&hip->extents_lock);
	hip->phys_size = inode->i_size;
	hip->fs_blocks = (inode->i_size + sb->s_blocksize - 1) >>
		sb->s_blocksize_bits;
	inode_set_bytes(inode, hip->fs_blocks << sb->s_blocksize_bits);
	hfsplus_mark_inode_dirty(inode, HFSPLUS_I_ALLOC_DIRTY);
}
