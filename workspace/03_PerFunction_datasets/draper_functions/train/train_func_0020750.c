loop_prepare_queue(struct loop_device *lo)
{
	init_kthread_worker(&lo->worker);
	lo->worker_task = kthread_run(kthread_worker_fn,
			&lo->worker, "loop%d", lo->lo_number);
	if (IS_ERR(lo->worker_task))
		return -ENOMEM;
	set_user_nice(lo->worker_task, MIN_NICE);
	return 0;
}
