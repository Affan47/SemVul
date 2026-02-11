is_cowonly_root(u64 root_objectid)
{
	if (root_objectid == BTRFS_ROOT_TREE_OBJECTID ||
	    root_objectid == BTRFS_EXTENT_TREE_OBJECTID ||
	    root_objectid == BTRFS_CHUNK_TREE_OBJECTID ||
	    root_objectid == BTRFS_DEV_TREE_OBJECTID ||
	    root_objectid == BTRFS_TREE_LOG_OBJECTID ||
	    root_objectid == BTRFS_CSUM_TREE_OBJECTID ||
	    root_objectid == BTRFS_UUID_TREE_OBJECTID ||
	    root_objectid == BTRFS_QUOTA_TREE_OBJECTID)
		return 1;
	return 0;
}
