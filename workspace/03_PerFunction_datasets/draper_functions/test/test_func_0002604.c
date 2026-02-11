view_stack_update(void)
{
	if (views[VIEW_STACK].dirty)
	{
		DebugState state = thread_state >= THREAD_STOPPED ? DS_DEBUG : DS_READY;
		view_update_unconditional(VIEW_STACK, state);
		return state == DS_DEBUG;
	}

	return FALSE;
}
