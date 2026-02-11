drbd_bm_lock(struct drbd_device *device, char *why, enum bm_flag flags)
{
	struct drbd_bitmap *b = device->bitmap;
	int trylock_failed;

	if (!b) {
		drbd_err(device, "FIXME no bitmap in drbd_bm_lock!?\n");
		return;
	}

	trylock_failed = !mutex_trylock(&b->bm_change);

	if (trylock_failed) {
		drbd_warn(device, "%s[%d] going to '%s' but bitmap already locked for '%s' by %s[%d]\n",
			  current->comm, task_pid_nr(current),
			  why, b->bm_why ?: "?",
			  b->bm_task->comm, task_pid_nr(b->bm_task));
		mutex_lock(&b->bm_change);
	}
	if (BM_LOCKED_MASK & b->bm_flags)
		drbd_err(device, "FIXME bitmap already locked in bm_lock\n");
	b->bm_flags |= flags & BM_LOCKED_MASK;

	b->bm_why  = why;
	b->bm_task = current;
}
