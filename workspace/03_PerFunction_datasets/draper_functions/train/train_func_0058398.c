elevator_init(struct request_queue *q, char *name)
{
	struct elevator_type *e = NULL;
	int err;


	lockdep_assert_held(&q->sysfs_lock);

	if (unlikely(q->elevator))
		return 0;

	INIT_LIST_HEAD(&q->queue_head);
	q->last_merge = NULL;
	q->end_sector = 0;
	q->boundary_rq = NULL;

	if (name) {
		e = elevator_get(name, true);
		if (!e)
			return -EINVAL;
	}


	if (!e && *chosen_elevator) {
		e = elevator_get(chosen_elevator, false);
		if (!e)
			printk(KERN_ERR "I/O scheduler %s not found\n",
							chosen_elevator);
	}

	if (!e) {
		e = elevator_get(CONFIG_DEFAULT_IOSCHED, false);
		if (!e) {
			printk(KERN_ERR
				"Default I/O scheduler not found. " \
				"Using noop.\n");
			e = elevator_get("noop", false);
		}
	}

	err = e->ops.elevator_init_fn(q, e);
	if (err)
		elevator_put(e);
	return err;
}
