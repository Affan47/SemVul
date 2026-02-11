btrfs_reloc_post_snapshot(struct btrfs_trans_handle *trans,
			       struct btrfs_pending_snapshot *pending)
{
	struct btrfs_root *root = pending->root;
	struct btrfs_root *reloc_root;
	struct btrfs_root *new_root;
	struct reloc_control *rc;
	int ret;

	if (!root->reloc_root)
		return 0;

	rc = root->fs_info->reloc_ctl;
	rc->merging_rsv_size += rc->nodes_relocated;

	if (rc->merge_reloc_tree) {
		ret = btrfs_block_rsv_migrate(&pending->block_rsv,
					      rc->block_rsv,
					      rc->nodes_relocated);
		if (ret)
			return ret;
	}

	new_root = pending->snap;
	reloc_root = create_reloc_root(trans, root->reloc_root,
				       new_root->root_key.objectid);
	if (IS_ERR(reloc_root))
		return PTR_ERR(reloc_root);

	ret = __add_reloc_root(reloc_root);
	BUG_ON(ret < 0);
	new_root->reloc_root = reloc_root;

	if (rc->create_reloc_tree)
		ret = clone_backref_node(trans, rc, root, reloc_root);
	return ret;
}
