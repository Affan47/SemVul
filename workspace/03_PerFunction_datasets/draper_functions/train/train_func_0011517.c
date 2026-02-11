coredump_finish(struct mm_struct *mm, bool core_dumped)
{
	struct core_thread *curr, *next;
	struct task_struct *task;

	spin_lock_irq(&current->sighand->siglock);
	if (core_dumped && !__fatal_signal_pending(current))
		current->signal->group_exit_code |= 0x80;
	current->signal->group_exit_task = NULL;
	current->signal->flags = SIGNAL_GROUP_EXIT;
	spin_unlock_irq(&current->sighand->siglock);

	next = mm->core_state->dumper.next;
	while ((curr = next) != NULL) {
		next = curr->next;
		task = curr->task;


		smp_mb();
		curr->task = NULL;
		wake_up_process(task);
	}

	mm->core_state = NULL;
}
