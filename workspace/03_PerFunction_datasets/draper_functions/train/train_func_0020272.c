mutex_remove_waiter(struct mutex *lock, struct mutex_waiter *waiter,
			 struct thread_info *ti)
{
	DEBUG_LOCKS_WARN_ON(list_empty(&waiter->list));
	DEBUG_LOCKS_WARN_ON(waiter->task != ti->task);
	DEBUG_LOCKS_WARN_ON(ti->task->blocked_on != waiter);
	ti->task->blocked_on = NULL;

	list_del_init(&waiter->list);
	waiter->task = NULL;
}
