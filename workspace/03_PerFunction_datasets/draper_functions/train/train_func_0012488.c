blkdev_pr_clear(struct block_device *bdev,
		struct pr_clear __user *arg)
{
	const struct pr_ops *ops = bdev->bd_disk->fops->pr_ops;
	struct pr_clear c;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;
	if (!ops || !ops->pr_clear)
		return -EOPNOTSUPP;
	if (copy_from_user(&c, arg, sizeof(c)))
		return -EFAULT;

	if (c.flags)
		return -EOPNOTSUPP;
	return ops->pr_clear(bdev, c.key);
}
