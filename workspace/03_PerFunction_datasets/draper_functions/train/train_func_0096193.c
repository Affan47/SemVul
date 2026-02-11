afs_lookup(struct inode *dir, struct dentry *dentry,
				 unsigned int flags)
{
	struct afs_vnode *vnode;
	struct afs_fid fid;
	struct inode *inode;
	struct key *key;
	int ret;

	vnode = AFS_FS_I(dir);

	_enter("{%x:%u},%p{%pd},",
	       vnode->fid.vid, vnode->fid.vnode, dentry, dentry);

	ASSERTCMP(d_inode(dentry), ==, NULL);

	if (dentry->d_name.len >= AFSNAMEMAX) {
		_leave(" = -ENAMETOOLONG");
		return ERR_PTR(-ENAMETOOLONG);
	}

	if (test_bit(AFS_VNODE_DELETED, &vnode->flags)) {
		_leave(" = -ESTALE");
		return ERR_PTR(-ESTALE);
	}

	key = afs_request_key(vnode->volume->cell);
	if (IS_ERR(key)) {
		_leave(" = %ld [key]", PTR_ERR(key));
		return ERR_CAST(key);
	}

	ret = afs_validate(vnode, key);
	if (ret < 0) {
		key_put(key);
		_leave(" = %d [val]", ret);
		return ERR_PTR(ret);
	}

	ret = afs_do_lookup(dir, dentry, &fid, key);
	if (ret < 0) {
		inode = afs_try_auto_mntpt(ret, dentry, dir, key, &fid);
		if (!IS_ERR(inode)) {
			key_put(key);
			goto success;
		}

		ret = PTR_ERR(inode);
		key_put(key);
		if (ret == -ENOENT) {
			d_add(dentry, NULL);
			_leave(" = NULL [negative]");
			return NULL;
		}
		_leave(" = %d [do]", ret);
		return ERR_PTR(ret);
	}
	dentry->d_fsdata = (void *)(unsigned long) vnode->status.data_version;


	inode = afs_iget(dir->i_sb, key, &fid, NULL, NULL);
	key_put(key);
	if (IS_ERR(inode)) {
		_leave(" = %ld", PTR_ERR(inode));
		return ERR_CAST(inode);
	}

success:
	d_add(dentry, inode);
	_leave(" = 0 { vn=%u u=%u } -> { ino=%lu v=%u }",
	       fid.vnode,
	       fid.unique,
	       d_inode(dentry)->i_ino,
	       d_inode(dentry)->i_generation);

	return NULL;
}
