bg_task_switch(struct bgtask *bt, int target)
{
	struct bgtask *old = current_task;

	g_assert(bt == NULL || !(bt->flags & TASK_F_RUNNING));

	if (old) {
		bg_task_suspend(old, target);
		current_task = NULL;
	}
	if (bt) {
		bg_task_check(bt);
		bg_task_resume(bt);
		current_task = bt;
	}
	return old;
}
