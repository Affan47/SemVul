dm_pr_preempt(struct block_device *bdev, u64 old_key, u64 new_key,
		enum pr_type type, bool abort)
{
	struct mapped_device *md = bdev->bd_disk->private_data;
	const struct pr_ops *ops;
	struct dm_target *tgt;
	fmode_t mode;
	int srcu_idx, r;

	r = dm_get_live_table_for_ioctl(md, &tgt, &bdev, &mode, &srcu_idx);
	if (r < 0)
		return r;

	ops = bdev->bd_disk->fops->pr_ops;
	if (ops && ops->pr_preempt)
		r = ops->pr_preempt(bdev, old_key, new_key, type, abort);
	else
		r = -EOPNOTSUPP;

	dm_put_live_table(md, srcu_idx);
	return r;
}
