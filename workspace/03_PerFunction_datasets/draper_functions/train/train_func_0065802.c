dm_get_live_table_for_ioctl(struct mapped_device *md,
		struct dm_target **tgt, struct block_device **bdev,
		fmode_t *mode, int *srcu_idx)
{
	struct dm_table *map;
	int r;

retry:
	r = -ENOTTY;
	map = dm_get_live_table(md, srcu_idx);
	if (!map || !dm_table_get_size(map))
		goto out;


	if (dm_table_get_num_targets(map) != 1)
		goto out;

	*tgt = dm_table_get_target(map, 0);

	if (!(*tgt)->type->prepare_ioctl)
		goto out;

	if (dm_suspended_md(md)) {
		r = -EAGAIN;
		goto out;
	}

	r = (*tgt)->type->prepare_ioctl(*tgt, bdev, mode);
	if (r < 0)
		goto out;

	return r;

out:
	dm_put_live_table(md, *srcu_idx);
	if (r == -ENOTCONN && !fatal_signal_pending(current)) {
		msleep(10);
		goto retry;
	}
	return r;
}
