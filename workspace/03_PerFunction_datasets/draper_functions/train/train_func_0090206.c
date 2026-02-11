ext4_clear_blocks(handle_t *handle, struct inode *inode,
			     struct buffer_head *bh,
			     ext4_fsblk_t block_to_free,
			     unsigned long count, __le32 *first,
			     __le32 *last)
{
	__le32 *p;
	int	flags = EXT4_FREE_BLOCKS_VALIDATED;
	int	err;

	if (S_ISDIR(inode->i_mode) || S_ISLNK(inode->i_mode))
		flags |= EXT4_FREE_BLOCKS_FORGET | EXT4_FREE_BLOCKS_METADATA;
	else if (ext4_should_journal_data(inode))
		flags |= EXT4_FREE_BLOCKS_FORGET;

	if (!ext4_data_block_valid(EXT4_SB(inode->i_sb), block_to_free,
				   count)) {
		EXT4_ERROR_INODE(inode, "attempt to clear invalid "
				 "blocks %llu len %lu",
				 (unsigned long long) block_to_free, count);
		return 1;
	}

	if (try_to_extend_transaction(handle, inode)) {
		if (bh) {
			BUFFER_TRACE(bh, "call ext4_handle_dirty_metadata");
			err = ext4_handle_dirty_metadata(handle, inode, bh);
			if (unlikely(err))
				goto out_err;
		}
		err = ext4_mark_inode_dirty(handle, inode);
		if (unlikely(err))
			goto out_err;
		err = ext4_truncate_restart_trans(handle, inode,
					ext4_blocks_for_truncate(inode));
		if (unlikely(err))
			goto out_err;
		if (bh) {
			BUFFER_TRACE(bh, "retaking write access");
			err = ext4_journal_get_write_access(handle, bh);
			if (unlikely(err))
				goto out_err;
		}
	}

	for (p = first; p < last; p++)
		*p = 0;

	ext4_free_blocks(handle, inode, NULL, block_to_free, count, flags);
	return 0;
out_err:
	ext4_std_error(inode->i_sb, err);
	return err;
}
