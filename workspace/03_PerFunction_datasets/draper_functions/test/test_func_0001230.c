w_bitmap_io(struct drbd_work *w, int unused)
{
	struct drbd_device *device =
		container_of(w, struct drbd_device, bm_io_work.w);
	struct bm_io_work *work = &device->bm_io_work;
	int rv = -EIO;

	D_ASSERT(device, atomic_read(&device->ap_bio_cnt) == 0);

	if (get_ldev(device)) {
		drbd_bm_lock(device, work->why, work->flags);
		rv = work->io_fn(device);
		drbd_bm_unlock(device);
		put_ldev(device);
	}

	clear_bit_unlock(BITMAP_IO, &device->flags);
	wake_up(&device->misc_wait);

	if (work->done)
		work->done(device, rv);

	clear_bit(BITMAP_IO_QUEUED, &device->flags);
	work->why = NULL;
	work->flags = 0;

	return 0;
}
