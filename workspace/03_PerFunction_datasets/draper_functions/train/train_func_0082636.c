drbd_queue_bitmap_io(struct drbd_device *device,
			  int (*io_fn)(struct drbd_device *),
			  void (*done)(struct drbd_device *, int),
			  char *why, enum bm_flag flags)
{
	D_ASSERT(device, current == first_peer_device(device)->connection->worker.task);

	D_ASSERT(device, !test_bit(BITMAP_IO_QUEUED, &device->flags));
	D_ASSERT(device, !test_bit(BITMAP_IO, &device->flags));
	D_ASSERT(device, list_empty(&device->bm_io_work.w.list));
	if (device->bm_io_work.why)
		drbd_err(device, "FIXME going to queue '%s' but '%s' still pending?\n",
			why, device->bm_io_work.why);

	device->bm_io_work.io_fn = io_fn;
	device->bm_io_work.done = done;
	device->bm_io_work.why = why;
	device->bm_io_work.flags = flags;

	spin_lock_irq(&device->resource->req_lock);
	set_bit(BITMAP_IO, &device->flags);
	if (atomic_read(&device->ap_bio_cnt) == 0) {
		if (!test_and_set_bit(BITMAP_IO_QUEUED, &device->flags))
			drbd_queue_work(&first_peer_device(device)->connection->sender_work,
					&device->bm_io_work.w);
	}
	spin_unlock_irq(&device->resource->req_lock);
}
