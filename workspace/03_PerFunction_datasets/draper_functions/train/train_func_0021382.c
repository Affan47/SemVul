btrfs_del_root_ref(struct btrfs_trans_handle *trans,
		       struct btrfs_root *tree_root,
		       u64 root_id, u64 ref_id, u64 dirid, u64 *sequence,
		       const char *name, int name_len)

{
	struct btrfs_path *path;
	struct btrfs_root_ref *ref;
	struct extent_buffer *leaf;
	struct btrfs_key key;
	unsigned long ptr;
	int err = 0;
	int ret;

	path = btrfs_alloc_path();
	if (!path)
		return -ENOMEM;

	key.objectid = root_id;
	key.type = BTRFS_ROOT_BACKREF_KEY;
	key.offset = ref_id;
again:
	ret = btrfs_search_slot(trans, tree_root, &key, path, -1, 1);
	BUG_ON(ret < 0);
	if (ret == 0) {
		leaf = path->nodes[0];
		ref = btrfs_item_ptr(leaf, path->slots[0],
				     struct btrfs_root_ref);

		WARN_ON(btrfs_root_ref_dirid(leaf, ref) != dirid);
		WARN_ON(btrfs_root_ref_name_len(leaf, ref) != name_len);
		ptr = (unsigned long)(ref + 1);
		WARN_ON(memcmp_extent_buffer(leaf, name, ptr, name_len));
		*sequence = btrfs_root_ref_sequence(leaf, ref);

		ret = btrfs_del_item(trans, tree_root, path);
		if (ret) {
			err = ret;
			goto out;
		}
	} else
		err = -ENOENT;

	if (key.type == BTRFS_ROOT_BACKREF_KEY) {
		btrfs_release_path(path);
		key.objectid = ref_id;
		key.type = BTRFS_ROOT_REF_KEY;
		key.offset = root_id;
		goto again;
	}

out:
	btrfs_free_path(path);
	return err;
}
