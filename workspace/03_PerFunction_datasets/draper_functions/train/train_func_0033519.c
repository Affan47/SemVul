get_task_io_context(struct task_struct *task,
				       gfp_t gfp_flags, int node)
{
	struct io_context *ioc;

	might_sleep_if(gfpflags_allow_blocking(gfp_flags));

	do {
		task_lock(task);
		ioc = task->io_context;
		if (likely(ioc)) {
			get_io_context(ioc);
			task_unlock(task);
			return ioc;
		}
		task_unlock(task);
	} while (!create_task_io_context(task, gfp_flags, node));

	return NULL;
}
