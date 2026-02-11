glfs_h_mkdir (struct glfs *fs, struct glfs_object *parent, const char *path,
	      mode_t mode, struct stat *stat)
{
	int                 ret = -1;
	xlator_t           *subvol = NULL;
	inode_t            *inode = NULL;
	loc_t               loc = {0, };
	struct iatt         iatt = {0, };
	uuid_t              gfid;
	dict_t             *xattr_req = NULL;
	struct glfs_object *object = NULL;


	if ((fs == NULL) || (parent == NULL) || (path == NULL)) {
		errno = EINVAL;
		return NULL;
	}

	__glfs_entry_fs (fs);


	subvol = glfs_active_subvol (fs);
	if (!subvol) {
		ret = -1;
		errno = EIO;
		goto out;
	}


	inode = glfs_resolve_inode (fs, subvol, parent);
	if (!inode) {
		errno = ESTALE;
		goto out;
	}

	xattr_req = dict_new ();
	if (!xattr_req) {
		ret = -1;
		errno = ENOMEM;
		goto out;
	}

	uuid_generate (gfid);
	ret = dict_set_static_bin (xattr_req, "gfid-req", gfid, 16);
	if (ret) {
		ret = -1;
		errno = ENOMEM;
		goto out;
	}

	GLFS_LOC_FILL_PINODE (inode, loc, ret, errno, out, path);


	ret = syncop_mkdir (subvol, &loc, mode, xattr_req, &iatt);


	if ( ret == 0 )  {
		ret = glfs_loc_link (&loc, &iatt);
		if (ret != 0) {
			goto out;
		}

		if (stat)
			glfs_iatt_to_stat (fs, &iatt, stat);

		ret = glfs_create_object (&loc, &object);
	}

out:
	if (ret && object != NULL) {
		glfs_h_close (object);
		object = NULL;
	}

	loc_wipe(&loc);

	if (inode)
		inode_unref (inode);

	if (xattr_req)
		dict_unref (xattr_req);

	glfs_subvol_done (fs, subvol);

	return object;
}
