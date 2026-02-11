v9fs_vfs_symlink_dotl(struct inode *dir, struct dentry *dentry,
		const char *symname)
{
	int err;
	kgid_t gid;
	char *name;
	struct p9_qid qid;
	struct inode *inode;
	struct p9_fid *dfid;
	struct p9_fid *fid = NULL;
	struct v9fs_session_info *v9ses;

	name = (char *) dentry->d_name.name;
	p9_debug(P9_DEBUG_VFS, "%lu,%s,%s\n", dir->i_ino, name, symname);
	v9ses = v9fs_inode2v9ses(dir);

	dfid = v9fs_fid_lookup(dentry->d_parent);
	if (IS_ERR(dfid)) {
		err = PTR_ERR(dfid);
		p9_debug(P9_DEBUG_VFS, "fid lookup failed %d\n", err);
		return err;
	}

	gid = v9fs_get_fsgid_for_create(dir);


	err = p9_client_symlink(dfid, name, (char *)symname, gid, &qid);

	if (err < 0) {
		p9_debug(P9_DEBUG_VFS, "p9_client_symlink failed %d\n", err);
		goto error;
	}

	v9fs_invalidate_inode_attr(dir);
	if (v9ses->cache == CACHE_LOOSE || v9ses->cache == CACHE_FSCACHE) {

		fid = p9_client_walk(dfid, 1, &name, 1);
		if (IS_ERR(fid)) {
			err = PTR_ERR(fid);
			p9_debug(P9_DEBUG_VFS, "p9_client_walk failed %d\n",
				 err);
			fid = NULL;
			goto error;
		}


		inode = v9fs_get_new_inode_from_fid(v9ses, fid, dir->i_sb);
		if (IS_ERR(inode)) {
			err = PTR_ERR(inode);
			p9_debug(P9_DEBUG_VFS, "inode creation failed %d\n",
				 err);
			goto error;
		}
		v9fs_fid_add(dentry, fid);
		d_instantiate(dentry, inode);
		fid = NULL;
		err = 0;
	} else {

		inode = v9fs_get_inode(dir->i_sb, S_IFLNK, 0);
		if (IS_ERR(inode)) {
			err = PTR_ERR(inode);
			goto error;
		}
		d_instantiate(dentry, inode);
	}

error:
	if (fid)
		p9_client_clunk(fid);

	return err;
}
