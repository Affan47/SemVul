fill_with_dentries(struct dir_context *ctx, const char *name, int namelen,
		   loff_t offset, u64 ino, unsigned int d_type)
{
	struct reiserfs_dentry_buf *dbuf =
		container_of(ctx, struct reiserfs_dentry_buf, ctx);
	struct dentry *dentry;

	WARN_ON_ONCE(!mutex_is_locked(&d_inode(dbuf->xadir)->i_mutex));

	if (dbuf->count == ARRAY_SIZE(dbuf->dentries))
		return -ENOSPC;

	if (name[0] == '.' && (namelen < 2 ||
			       (namelen == 2 && name[1] == '.')))
		return 0;

	dentry = lookup_one_len(name, dbuf->xadir, namelen);
	if (IS_ERR(dentry)) {
		return PTR_ERR(dentry);
	} else if (d_really_is_negative(dentry)) {

		reiserfs_error(dentry->d_sb, "xattr-20003",
			       "Corrupted directory: xattr %pd listed but "
			       "not found for file %pd.\n",
			       dentry, dbuf->xadir);
		dput(dentry);
		return -EIO;
	}

	dbuf->dentries[dbuf->count++] = dentry;
	return 0;
}
