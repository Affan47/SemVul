mono_thread_resume (MonoInternalThread *thread)
{
	LOCK_THREAD (thread);

	if ((thread->state & ThreadState_SuspendRequested) != 0) {
		thread->state &= ~ThreadState_SuspendRequested;
		UNLOCK_THREAD (thread);
		return TRUE;
	}

	if ((thread->state & ThreadState_Suspended) == 0 ||
		(thread->state & ThreadState_Unstarted) != 0 ||
		(thread->state & ThreadState_Aborted) != 0 ||
		(thread->state & ThreadState_Stopped) != 0)
	{
		UNLOCK_THREAD (thread);
		return FALSE;
	}

	return resume_thread_internal (thread);
}
