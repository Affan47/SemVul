mark_oom_victim(struct task_struct *tsk)
{
	WARN_ON(oom_killer_disabled);

	if (test_and_set_tsk_thread_flag(tsk, TIF_MEMDIE))
		return;


	__thaw_task(tsk);
	atomic_inc(&oom_victims);
}
