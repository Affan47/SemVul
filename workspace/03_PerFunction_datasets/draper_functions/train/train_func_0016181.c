manage_global_listener_queue(struct task *t)
{
	int next = TICK_ETERNITY;

	if (LIST_ISEMPTY(&global_listener_queue))
		goto out;


	if (unlikely(actconn >= global.maxconn))
		goto out;


	dequeue_all_listeners(&global_listener_queue);

 out:
	t->expire = next;
	task_queue(t);
	return t;
}
