ttm_read_lock(struct ttm_lock *lock, bool interruptible)
{
	int ret = 0;

	if (interruptible)
		ret = wait_event_interruptible(lock->queue,
					       __ttm_read_lock(lock));
	else
		wait_event(lock->queue, __ttm_read_lock(lock));
	return ret;
}
