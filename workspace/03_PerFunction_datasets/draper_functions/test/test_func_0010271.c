configfs_depend_prep(struct dentry *origin,
				struct config_item *target)
{
	struct configfs_dirent *child_sd, *sd;
	int ret = 0;

	BUG_ON(!origin || !origin->d_fsdata);
	sd = origin->d_fsdata;

	if (sd->s_element == target)
		goto out;

	list_for_each_entry(child_sd, &sd->s_children, s_sibling) {
		if ((child_sd->s_type & CONFIGFS_DIR) &&
		    !(child_sd->s_type & CONFIGFS_USET_DROPPING) &&
		    !(child_sd->s_type & CONFIGFS_USET_CREATING)) {
			ret = configfs_depend_prep(child_sd->s_dentry,
						   target);
			if (!ret)
				goto out;
		}
	}


	ret = -ENOENT;

out:
	return ret;
}
