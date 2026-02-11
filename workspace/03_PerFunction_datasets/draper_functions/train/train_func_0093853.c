auxdev_open(struct inode *inode, struct file *file)
{
	unsigned int minor = iminor(inode);
	struct drm_dp_aux_dev *aux_dev;

	aux_dev = drm_dp_aux_dev_get_by_minor(minor);
	if (!aux_dev)
		return -ENODEV;

	file->private_data = aux_dev;
	return 0;
}
