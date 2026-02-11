quotactl_block(const char __user *special, int cmd)
{
#ifdef CONFIG_BLOCK
	struct block_device *bdev;
	struct super_block *sb;
	struct filename *tmp = getname(special);

	if (IS_ERR(tmp))
		return ERR_CAST(tmp);
	bdev = lookup_bdev(tmp->name, 0);
	putname(tmp);
	if (IS_ERR(bdev))
		return ERR_CAST(bdev);
	if (quotactl_cmd_write(cmd))
		sb = get_super_thawed(bdev);
	else
		sb = get_super(bdev);
	bdput(bdev);
	if (!sb)
		return ERR_PTR(-ENODEV);

	return sb;
#else
	return ERR_PTR(-ENODEV);
#endif
}
