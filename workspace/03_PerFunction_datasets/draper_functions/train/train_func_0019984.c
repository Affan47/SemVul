new_pts_fs_info(struct super_block *sb)
{
	struct pts_fs_info *fsi;

	fsi = kzalloc(sizeof(struct pts_fs_info), GFP_KERNEL);
	if (!fsi)
		return NULL;

	ida_init(&fsi->allocated_ptys);
	fsi->mount_opts.mode = DEVPTS_DEFAULT_MODE;
	fsi->mount_opts.ptmxmode = DEVPTS_DEFAULT_PTMX_MODE;
	fsi->sb = sb;

	return fsi;
}
