rawdata_open(struct inode *inode, struct file *file)
{
	struct aa_proxy *proxy = inode->i_private;
	struct aa_label *label;
	struct aa_profile *profile;

	if (!policy_view_capable(NULL))
		return -EACCES;
	label = aa_get_label_rcu(&proxy->label);
	profile = labels_profile(label);
	file->private_data = aa_get_loaddata(profile->rawdata);
	aa_put_label(label);

	return 0;
}
