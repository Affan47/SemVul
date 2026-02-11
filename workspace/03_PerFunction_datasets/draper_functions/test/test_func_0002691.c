is_kernel_thread(ulong task)
{
	struct task_context *tc;
	ulong mm;

	tc = task_to_context(task);

	if ((tc->pid == 0) && !STREQ(tc->comm, pc->program_name))
		return TRUE;

        if (_ZOMBIE_ == TASK_STATE_UNINITIALIZED)
                initialize_task_state();

	if (IS_ZOMBIE(task) || IS_EXITING(task))
                return FALSE;


	mm = task_mm(task, TRUE);

	if (ACTIVE() && (mm != tc->mm_struct))
		return FALSE;


        if (!tc->mm_struct) {
		if (IS_EXITING(task))
			return FALSE;

		if (!task_state(task) && !task_flags(task))
			return FALSE;

		return TRUE;

	} else if (tc->mm_struct == symbol_value("init_mm"))
		return TRUE;

	return FALSE;
}
