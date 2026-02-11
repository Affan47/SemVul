send_write_or_clone(struct send_ctx *sctx,
			       struct btrfs_path *path,
			       struct btrfs_key *key,
			       struct clone_root *clone_root)
{
	int ret = 0;
	struct btrfs_file_extent_item *ei;
	u64 offset = key->offset;
	u64 len;
	u8 type;
	u64 bs = sctx->send_root->fs_info->sb->s_blocksize;

	ei = btrfs_item_ptr(path->nodes[0], path->slots[0],
			struct btrfs_file_extent_item);
	type = btrfs_file_extent_type(path->nodes[0], ei);
	if (type == BTRFS_FILE_EXTENT_INLINE) {
		len = btrfs_file_extent_inline_len(path->nodes[0],
						   path->slots[0], ei);


		len = PAGE_CACHE_ALIGN(len);
	} else {
		len = btrfs_file_extent_num_bytes(path->nodes[0], ei);
	}

	if (offset + len > sctx->cur_inode_size)
		len = sctx->cur_inode_size - offset;
	if (len == 0) {
		ret = 0;
		goto out;
	}

	if (clone_root && IS_ALIGNED(offset + len, bs)) {
		u64 disk_byte;
		u64 data_offset;

		disk_byte = btrfs_file_extent_disk_bytenr(path->nodes[0], ei);
		data_offset = btrfs_file_extent_offset(path->nodes[0], ei);
		ret = clone_range(sctx, clone_root, disk_byte, data_offset,
				  offset, len);
	} else {
		ret = send_extent_data(sctx, offset, len);
	}
out:
	return ret;
}
