configfs_hash_and_remove(struct dentry * dir, const char * name)
{
	struct configfs_dirent * sd;
	struct configfs_dirent * parent_sd = dir->d_fsdata;

	if (d_really_is_negative(dir))

		return;

	mutex_lock(&d_inode(dir)->i_mutex);
	list_for_each_entry(sd, &parent_sd->s_children, s_sibling) {
		if (!sd->s_element)
			continue;
		if (!strcmp(configfs_get_name(sd), name)) {
			spin_lock(&configfs_dirent_lock);
			list_del_init(&sd->s_sibling);
			spin_unlock(&configfs_dirent_lock);
			configfs_drop_dentry(sd, dir);
			configfs_put(sd);
			break;
		}
	}
	mutex_unlock(&d_inode(dir)->i_mutex);
}
