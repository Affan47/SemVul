ves_icall_System_Threading_Thread_Resume (MonoThread *thread)
{
	if (!thread->internal_thread) {
		mono_set_pending_exception (mono_get_exception_thread_state ("Thread has not been started, or is dead."));
	} else {
		LOCK_THREAD (thread->internal_thread);
		if (!mono_thread_resume (thread->internal_thread))
			mono_set_pending_exception (mono_get_exception_thread_state ("Thread has not been started, or is dead."));
		UNLOCK_THREAD (thread->internal_thread);
	}
}
