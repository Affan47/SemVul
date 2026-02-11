bl_up_write(struct block_lock *lock)
{
	spin_lock(&lock->lock);
	__del_holder(lock, current);
	lock->count = 0;
	if (!list_empty(&lock->waiters))
		__wake_many(lock);
	spin_unlock(&lock->lock);
}
