record_reloc_root_in_trans(struct btrfs_trans_handle *trans,
				      struct btrfs_root *reloc_root)
{
	struct btrfs_root *root;

	if (reloc_root->last_trans == trans->transid)
		return 0;

	root = read_fs_root(reloc_root->fs_info, reloc_root->root_key.offset);
	BUG_ON(IS_ERR(root));
	BUG_ON(root->reloc_root != reloc_root);

	return btrfs_record_root_in_trans(trans, root);
}
