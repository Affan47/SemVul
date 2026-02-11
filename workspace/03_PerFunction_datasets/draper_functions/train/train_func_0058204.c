get_ext_path(struct inode *inode, ext4_lblk_t lblock,
		struct ext4_ext_path **ppath)
{
	struct ext4_ext_path *path;

	path = ext4_find_extent(inode, lblock, ppath, EXT4_EX_NOCACHE);
	if (IS_ERR(path))
		return PTR_ERR(path);
	if (path[ext_depth(inode)].p_ext == NULL) {
		ext4_ext_drop_refs(path);
		kfree(path);
		*ppath = NULL;
		return -ENODATA;
	}
	*ppath = path;
	return 0;
}
