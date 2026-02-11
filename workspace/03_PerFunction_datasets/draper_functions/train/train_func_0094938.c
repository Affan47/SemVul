aufs_open_dir(struct inode *inode __maybe_unused,
			 struct file *file)
{
	int err;
	struct super_block *sb;
	struct au_fidir *fidir;

	err = -ENOMEM;
	sb = file->f_path.dentry->d_sb;
	si_read_lock(sb, AuLock_FLUSH);
	fidir = au_fidir_alloc(sb);
	if (fidir) {
		struct au_do_open_args args = {
			.open	= do_open_dir,
			.fidir	= fidir
		};
		err = au_do_open(file, &args);
		if (unlikely(err))
			kfree(fidir);
	}
	si_read_unlock(sb);
	return err;
}
