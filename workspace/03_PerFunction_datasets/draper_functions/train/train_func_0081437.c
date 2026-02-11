btrfs_block_rsv_refill(struct btrfs_root *root,
			   struct btrfs_block_rsv *block_rsv, u64 min_reserved,
			   enum btrfs_reserve_flush_enum flush)
{
	u64 num_bytes = 0;
	int ret = -ENOSPC;

	if (!block_rsv)
		return 0;

	spin_lock(&block_rsv->lock);
	num_bytes = min_reserved;
	if (block_rsv->reserved >= num_bytes)
		ret = 0;
	else
		num_bytes -= block_rsv->reserved;
	spin_unlock(&block_rsv->lock);

	if (!ret)
		return 0;

	ret = reserve_metadata_bytes(root, block_rsv, num_bytes, flush);
	if (!ret) {
		block_rsv_add_bytes(block_rsv, num_bytes, 0);
		return 0;
	}

	return ret;
}
