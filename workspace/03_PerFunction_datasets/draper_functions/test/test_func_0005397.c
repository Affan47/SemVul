sas_alloc_task(gfp_t flags)
{
	struct sas_task *task = kmem_cache_zalloc(sas_task_cache, flags);

	if (task) {
		spin_lock_init(&task->task_state_lock);
		task->task_state_flags = SAS_TASK_STATE_PENDING;
	}

	return task;
}
