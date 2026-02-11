decode_by_dir_ino(struct super_block *sb, ino_t ino,
					ino_t dir_ino,
					struct au_nfsd_si_lock *nsi_lock)
{
	struct dentry *dentry;
	struct path path;

	if (dir_ino != AUFS_ROOT_INO) {
		path.dentry = decode_by_ino(sb, dir_ino, 0);
		dentry = path.dentry;
		if (!path.dentry || IS_ERR(path.dentry))
			goto out;
		AuDebugOn(au_test_anon(path.dentry));
	} else
		path.dentry = dget(sb->s_root);

	path.mnt = au_mnt_get(sb);
	dentry = au_lkup_by_ino(&path, ino, nsi_lock);
	path_put(&path);

out:
	AuTraceErrPtr(dentry);
	return dentry;
}
