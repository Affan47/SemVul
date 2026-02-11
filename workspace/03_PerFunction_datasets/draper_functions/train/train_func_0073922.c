prepare_to_relocate(struct reloc_control *rc)
{
	struct btrfs_trans_handle *trans;

	rc->block_rsv = btrfs_alloc_block_rsv(rc->extent_root,
					      BTRFS_BLOCK_RSV_TEMP);
	if (!rc->block_rsv)
		return -ENOMEM;

	memset(&rc->cluster, 0, sizeof(rc->cluster));
	rc->search_start = rc->block_group->key.objectid;
	rc->extents_found = 0;
	rc->nodes_relocated = 0;
	rc->merging_rsv_size = 0;
	rc->reserved_bytes = 0;
	rc->block_rsv->size = rc->extent_root->nodesize *
			      RELOCATION_RESERVED_NODES;

	rc->create_reloc_tree = 1;
	set_reloc_control(rc);

	trans = btrfs_join_transaction(rc->extent_root);
	if (IS_ERR(trans)) {
		unset_reloc_control(rc);


		return PTR_ERR(trans);
	}
	btrfs_commit_transaction(trans, rc->extent_root);
	return 0;
}
