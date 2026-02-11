aa_bind_mount(struct aa_label *label, const struct path *path,
		  const char *dev_name, unsigned long flags)
{
	struct aa_profile *profile;
	char *buffer = NULL, *old_buffer = NULL;
	struct path old_path;
	int error;

	AA_BUG(!label);
	AA_BUG(!path);

	if (!dev_name || !*dev_name)
		return -EINVAL;

	flags &= MS_REC | MS_BIND;

	error = kern_path(dev_name, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &old_path);
	if (error)
		return error;

	get_buffers(buffer, old_buffer);
	error = fn_for_each_confined(label, profile,
			match_mnt(profile, path, buffer, &old_path, old_buffer,
				  NULL, flags, NULL, false));
	put_buffers(buffer, old_buffer);
	path_put(&old_path);

	return error;
}
