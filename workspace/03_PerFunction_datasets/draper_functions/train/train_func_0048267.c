mono_thread_current_check_pending_interrupt ()
{
	MonoInternalThread *thread = mono_thread_internal_current ();
	gboolean throw = FALSE;

	LOCK_THREAD (thread);

	if (thread->thread_interrupt_requested) {
		throw = TRUE;
		thread->thread_interrupt_requested = FALSE;
	}

	UNLOCK_THREAD (thread);

	if (throw) {
		mono_raise_exception (mono_get_exception_thread_interrupted ());
	}
}
