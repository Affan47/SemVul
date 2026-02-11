apparmor_path_link(struct dentry *old_dentry, const struct path *new_dir,
			      struct dentry *new_dentry)
{
	struct aa_label *label;
	int error = 0;

	if (!path_mediated_fs(old_dentry))
		return 0;

	label = aa_begin_current_label(DO_UPDATE);
	if (!unconfined(label))
		error = aa_path_link(label, old_dentry, new_dir, new_dentry);
	aa_end_current_label(label);

	return error;
}
