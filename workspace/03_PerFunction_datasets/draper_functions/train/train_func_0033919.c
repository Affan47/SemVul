b43legacy_debugfs_write(struct file *file,
				 const char __user *userbuf,
				 size_t count, loff_t *ppos)
{
	struct b43legacy_wldev *dev;
	struct b43legacy_debugfs_fops *dfops;
	char *buf;
	int err = 0;

	if (!count)
		return 0;
	if (count > PAGE_SIZE)
		return -E2BIG;
	dev = file->private_data;
	if (!dev)
		return -ENODEV;

	mutex_lock(&dev->wl->mutex);
	if (b43legacy_status(dev) < B43legacy_STAT_INITIALIZED) {
		err = -ENODEV;
		goto out_unlock;
	}

	dfops = container_of(file->f_op, struct b43legacy_debugfs_fops, fops);
	if (!dfops->write) {
		err = -ENOSYS;
		goto out_unlock;
	}

	buf = (char *)get_zeroed_page(GFP_KERNEL);
	if (!buf) {
		err = -ENOMEM;
		goto out_unlock;
	}
	if (copy_from_user(buf, userbuf, count)) {
		err = -EFAULT;
		goto out_freepage;
	}
	if (dfops->take_irqlock) {
		spin_lock_irq(&dev->wl->irq_lock);
		err = dfops->write(dev, buf, count);
		spin_unlock_irq(&dev->wl->irq_lock);
	} else
		err = dfops->write(dev, buf, count);
	if (err)
		goto out_freepage;

out_freepage:
	free_page((unsigned long)buf);
out_unlock:
	mutex_unlock(&dev->wl->mutex);

	return err ? err : count;
}
