au_br_stfs(struct au_branch *br, struct aufs_stfs *stfs)
{
	int err;
	struct kstatfs kstfs;

	err = vfs_statfs(&br->br_path, &kstfs);
	if (!err) {
		stfs->f_blocks = kstfs.f_blocks;
		stfs->f_bavail = kstfs.f_bavail;
		stfs->f_files = kstfs.f_files;
		stfs->f_ffree = kstfs.f_ffree;
	}

	return err;
}
