configfs_lookup(struct inode *dir,
				       struct dentry *dentry,
				       unsigned int flags)
{
	struct configfs_dirent * parent_sd = dentry->d_parent->d_fsdata;
	struct configfs_dirent * sd;
	int found = 0;
	int err;


	err = -ENOENT;
	if (!configfs_dirent_is_ready(parent_sd))
		goto out;

	list_for_each_entry(sd, &parent_sd->s_children, s_sibling) {
		if (sd->s_type & CONFIGFS_NOT_PINNED) {
			const unsigned char * name = configfs_get_name(sd);

			if (strcmp(name, dentry->d_name.name))
				continue;

			found = 1;
			err = configfs_attach_attr(sd, dentry);
			break;
		}
	}

	if (!found) {


		if (dentry->d_name.len > NAME_MAX)
			return ERR_PTR(-ENAMETOOLONG);
		d_add(dentry, NULL);
		return NULL;
	}

out:
	return ERR_PTR(err);
}
