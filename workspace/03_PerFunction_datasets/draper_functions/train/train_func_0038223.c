multipath_prepare_ioctl(struct dm_target *ti,
		struct block_device **bdev, fmode_t *mode)
{
	struct multipath *m = ti->private;
	unsigned long flags;
	int r;

	spin_lock_irqsave(&m->lock, flags);

	if (!m->current_pgpath)
		__choose_pgpath(m, 0);

	if (m->current_pgpath) {
		if (!m->queue_io) {
			*bdev = m->current_pgpath->path.dev->bdev;
			*mode = m->current_pgpath->path.dev->mode;
			r = 0;
		} else {

			r = -ENOTCONN;
		}
	} else {

		if (m->queue_if_no_path)
			r = -ENOTCONN;
		else
			r = -EIO;
	}

	spin_unlock_irqrestore(&m->lock, flags);

	if (r == -ENOTCONN) {
		spin_lock_irqsave(&m->lock, flags);
		if (!m->current_pg) {

			__choose_pgpath(m, 0);
		}
		if (m->pg_init_required)
			__pg_init_all_paths(m);
		spin_unlock_irqrestore(&m->lock, flags);
		dm_table_run_md_queue_async(m->ti->table);
	}


	if (!r && ti->len != i_size_read((*bdev)->bd_inode) >> SECTOR_SHIFT)
		return 1;
	return r;
}
