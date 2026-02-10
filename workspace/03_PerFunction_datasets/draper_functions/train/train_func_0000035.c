media_open(struct inode *inode, struct file *filp)
{
	struct media_devnode *mdev;
	int ret;


	mutex_lock(&media_devnode_lock);
	mdev = container_of(inode->i_cdev, struct media_devnode, cdev);


	if (!media_devnode_is_registered(mdev)) {
		mutex_unlock(&media_devnode_lock);
		return -ENXIO;
	}

	get_device(&mdev->dev);
	mutex_unlock(&media_devnode_lock);

	filp->private_data = mdev;

	if (mdev->fops->open) {
		ret = mdev->fops->open(filp);
		if (ret) {
			put_device(&mdev->dev);
			return ret;
		}
	}

	return 0;
}
