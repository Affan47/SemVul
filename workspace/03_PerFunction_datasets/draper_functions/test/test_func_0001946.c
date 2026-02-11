__multipath_map(struct dm_target *ti, struct request *clone,
			   union map_info *map_context,
			   struct request *rq, struct request **__clone)
{
	struct multipath *m = (struct multipath *) ti->private;
	int r = DM_MAPIO_REQUEUE;
	size_t nr_bytes = clone ? blk_rq_bytes(clone) : blk_rq_bytes(rq);
	struct pgpath *pgpath;
	struct block_device *bdev;
	struct dm_mpath_io *mpio;

	spin_lock_irq(&m->lock);


	if (!m->current_pgpath ||
	    (!m->queue_io && (m->repeat_count && --m->repeat_count == 0)))
		__choose_pgpath(m, nr_bytes);

	pgpath = m->current_pgpath;

	if (!pgpath) {
		if (!__must_push_back(m))
			r = -EIO;
		goto out_unlock;
	} else if (m->queue_io || m->pg_init_required) {
		__pg_init_all_paths(m);
		goto out_unlock;
	}

	if (set_mapinfo(m, map_context) < 0)

		goto out_unlock;

	mpio = map_context->ptr;
	mpio->pgpath = pgpath;
	mpio->nr_bytes = nr_bytes;

	bdev = pgpath->path.dev->bdev;

	spin_unlock_irq(&m->lock);

	if (clone) {

		clone->q = bdev_get_queue(bdev);
		clone->rq_disk = bdev->bd_disk;
		clone->cmd_flags |= REQ_FAILFAST_TRANSPORT;
	} else {

		*__clone = blk_get_request(bdev_get_queue(bdev),
					   rq_data_dir(rq), GFP_ATOMIC);
		if (IS_ERR(*__clone)) {

			clear_mapinfo(m, map_context);
			return r;
		}
		(*__clone)->bio = (*__clone)->biotail = NULL;
		(*__clone)->rq_disk = bdev->bd_disk;
		(*__clone)->cmd_flags |= REQ_FAILFAST_TRANSPORT;
	}

	if (pgpath->pg->ps.type->start_io)
		pgpath->pg->ps.type->start_io(&pgpath->pg->ps,
					      &pgpath->path,
					      nr_bytes);
	return DM_MAPIO_REMAPPED;

out_unlock:
	spin_unlock_irq(&m->lock);

	return r;
}
