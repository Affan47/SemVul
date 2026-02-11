kfd_get_process(const struct task_struct *thread)
{
	struct kfd_process *process;

	if (thread->mm == NULL)
		return ERR_PTR(-EINVAL);


	if (thread->group_leader->mm != thread->mm)
		return ERR_PTR(-EINVAL);

	process = find_process(thread);

	return process;
}
