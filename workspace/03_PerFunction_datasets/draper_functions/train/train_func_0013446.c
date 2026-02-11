bl_init(struct block_lock *lock)
{
	int i;

	spin_lock_init(&lock->lock);
	lock->count = 0;
	INIT_LIST_HEAD(&lock->waiters);
	for (i = 0; i < MAX_HOLDERS; i++)
		lock->holders[i] = NULL;
}
