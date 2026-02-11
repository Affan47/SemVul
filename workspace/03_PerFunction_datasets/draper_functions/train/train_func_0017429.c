i915_forcewake_create(struct dentry *root, struct drm_minor *minor)
{
	struct drm_device *dev = minor->dev;
	struct dentry *ent;

	ent = debugfs_create_file("i915_forcewake_user",
				  S_IRUSR,
				  root, dev,
				  &i915_forcewake_fops);
	if (!ent)
		return -ENOMEM;

	return drm_add_fake_info_node(minor, ent, &i915_forcewake_fops);
}
