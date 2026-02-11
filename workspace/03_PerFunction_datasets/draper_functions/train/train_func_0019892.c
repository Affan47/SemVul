bg_sched_wakeup(struct bgtask *bt)
{
	bg_task_check(bt);
	g_assert(bt->flags & TASK_F_SLEEPING);
	g_assert(!(bt->flags & TASK_F_RUNNING));

	sleepq = g_slist_remove(sleepq, bt);
	bt->flags &= ~TASK_F_SLEEPING;
	bg_runcount++;
	bg_sched_add(bt);
}
