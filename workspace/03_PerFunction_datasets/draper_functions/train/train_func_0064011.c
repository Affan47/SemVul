task_work_add(struct task_struct *task, struct callback_head *work, bool notify)
{
	struct callback_head *head;

	do {
		head = ACCESS_ONCE(task->task_works);
		if (unlikely(head == &work_exited))
			return -ESRCH;
		work->next = head;
	} while (cmpxchg(&task->task_works, head, work) != head);

	if (notify)
		set_notify_resume(task);
	return 0;
}
