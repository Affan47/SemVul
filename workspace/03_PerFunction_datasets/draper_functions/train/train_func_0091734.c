proc_tid_comm_permission(struct inode *inode, int mask)
{
	bool is_same_tgroup;
	struct task_struct *task;

	task = get_proc_task(inode);
	if (!task)
		return -ESRCH;
	is_same_tgroup = same_thread_group(current, task);
	put_task_struct(task);

	if (likely(is_same_tgroup && !(mask & MAY_EXEC))) {


		return 0;
	}

	return generic_permission(inode, mask);
}
