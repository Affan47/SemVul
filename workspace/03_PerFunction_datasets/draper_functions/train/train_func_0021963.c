init_rq_based_worker_thread(struct mapped_device *md)
{

	init_kthread_worker(&md->kworker);
	md->kworker_task = kthread_run(kthread_worker_fn, &md->kworker,
				       "kdmwork-%s", dm_device_name(md));
}
