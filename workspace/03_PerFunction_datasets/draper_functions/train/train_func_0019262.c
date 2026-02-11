btrfs_fh_to_parent(struct super_block *sb, struct fid *fh,
					 int fh_len, int fh_type)
{
	struct btrfs_fid *fid = (struct btrfs_fid *) fh;
	u64 objectid, root_objectid;
	u32 generation;

	if (fh_type == FILEID_BTRFS_WITH_PARENT) {
		if (fh_len <  BTRFS_FID_SIZE_CONNECTABLE)
			return NULL;
		root_objectid = fid->root_objectid;
	} else if (fh_type == FILEID_BTRFS_WITH_PARENT_ROOT) {
		if (fh_len < BTRFS_FID_SIZE_CONNECTABLE_ROOT)
			return NULL;
		root_objectid = fid->parent_root_objectid;
	} else
		return NULL;

	objectid = fid->parent_objectid;
	generation = fid->parent_gen;

	return btrfs_get_dentry(sb, objectid, root_objectid, generation, 1);
}
