amdgpu_debugfs_regs_init(struct amdgpu_device *adev)
{
	struct drm_minor *minor = adev->ddev->primary;
	struct dentry *ent, *root = minor->debugfs_root;

	ent = debugfs_create_file("amdgpu_regs", S_IFREG | S_IRUGO, root,
				  adev, &amdgpu_debugfs_regs_fops);
	if (IS_ERR(ent))
		return PTR_ERR(ent);
	i_size_write(ent->d_inode, adev->rmmio_size);
	adev->debugfs_regs = ent;

	return 0;
}
