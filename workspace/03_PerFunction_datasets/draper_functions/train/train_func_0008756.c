intel_th_output_open(struct inode *inode, struct file *file)
{
	const struct file_operations *fops;
	struct intel_th_driver *thdrv;
	struct device *dev;
	int err;

	dev = bus_find_device(&intel_th_bus, NULL,
			      (void *)(unsigned long)inode->i_rdev,
			      match_devt);
	if (!dev || !dev->driver)
		return -ENODEV;

	thdrv = to_intel_th_driver(dev->driver);
	fops = fops_get(thdrv->fops);
	if (!fops)
		return -ENODEV;

	replace_fops(file, fops);

	file->private_data = to_intel_th_device(dev);

	if (file->f_op->open) {
		err = file->f_op->open(inode, file);
		return err;
	}

	return 0;
}
