cifs_prime_dcache(struct dentry *parent, struct qstr *name,
		    struct cifs_fattr *fattr)
{
	struct dentry *dentry, *alias;
	struct inode *inode;
	struct super_block *sb = d_inode(parent)->i_sb;
	struct cifs_sb_info *cifs_sb = CIFS_SB(sb);

	cifs_dbg(FYI, "%s: for %s\n", __func__, name->name);

	dentry = d_hash_and_lookup(parent, name);
	if (IS_ERR(dentry))
		return;

	if (dentry) {
		inode = d_inode(dentry);
		if (inode) {
			if (d_mountpoint(dentry))
				goto out;


			if (!(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_SERVER_INUM))
				fattr->cf_uniqueid = CIFS_I(inode)->uniqueid;


			if (CIFS_I(inode)->uniqueid == fattr->cf_uniqueid &&
			    (inode->i_mode & S_IFMT) ==
			    (fattr->cf_mode & S_IFMT)) {
				cifs_fattr_to_inode(inode, fattr);
				goto out;
			}
		}
		d_invalidate(dentry);
		dput(dentry);
	}


	if (fattr->cf_flags & CIFS_FATTR_NEED_REVAL)
		return;

	dentry = d_alloc(parent, name);
	if (!dentry)
		return;

	inode = cifs_iget(sb, fattr);
	if (!inode)
		goto out;

	alias = d_splice_alias(inode, dentry);
	if (alias && !IS_ERR(alias))
		dput(alias);
out:
	dput(dentry);
}
