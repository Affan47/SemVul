btrfs_alloc_dev_extent(struct btrfs_trans_handle *trans,
				  struct btrfs_device *device,
				  u64 chunk_tree, u64 chunk_objectid,
				  u64 chunk_offset, u64 start, u64 num_bytes)
{
	int ret;
	struct btrfs_path *path;
	struct btrfs_root *root = device->dev_root;
	struct btrfs_dev_extent *extent;
	struct extent_buffer *leaf;
	struct btrfs_key key;

	WARN_ON(!device->in_fs_metadata);
	WARN_ON(device->is_tgtdev_for_dev_replace);
	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	key.objectid = device->devid;
	key.offset = start;
	key.type = BTRFS_DEV_EXTENT_KEY;
	ret = btrfs_insert_empty_item(trans, root, path, &key,
				      sizeof(*extent));
	if (ret)
		goto out;

	leaf = path->nodes[0];
	extent = btrfs_item_ptr(leaf, path->slots[0],
				struct btrfs_dev_extent);
	btrfs_set_dev_extent_chunk_tree(leaf, extent, chunk_tree);
	btrfs_set_dev_extent_chunk_objectid(leaf, extent, chunk_objectid);
	btrfs_set_dev_extent_chunk_offset(leaf, extent, chunk_offset);

	write_extent_buffer(leaf, root->fs_info->chunk_tree_uuid,
		    btrfs_dev_extent_chunk_tree_uuid(extent), BTRFS_UUID_SIZE);

	btrfs_set_dev_extent_length(leaf, extent, num_bytes);
	btrfs_mark_buffer_dirty(leaf);
out:
	btrfs_free_path(path);
	return ret;
}
