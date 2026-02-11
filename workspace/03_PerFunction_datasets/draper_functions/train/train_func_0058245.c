ves_icall_System_Threading_Monitor_Monitor_pulse (MonoObject *obj)
{
	MonoThreadsSync *mon;

	LOCK_DEBUG (g_message ("%s: (%d) Pulsing %p", __func__, GetCurrentThreadId (), obj));

	mon = obj->synchronisation;
#ifdef HAVE_MOVING_COLLECTOR
	{
		LockWord lw;
		lw.sync = mon;
		if (lw.lock_word & LOCK_WORD_THIN_HASH) {
			mono_raise_exception (mono_get_exception_synchronization_lock ("Not locked"));
			return;
		}
		lw.lock_word &= ~LOCK_WORD_BITS_MASK;
		mon = lw.sync;
	}
#endif
	if (mon == NULL) {
		mono_raise_exception (mono_get_exception_synchronization_lock ("Not locked"));
		return;
	}
	if (mon->owner != GetCurrentThreadId ()) {
		mono_raise_exception (mono_get_exception_synchronization_lock ("Not locked by this thread"));
		return;
	}

	LOCK_DEBUG (g_message ("%s: (%d) %d threads waiting", __func__, GetCurrentThreadId (), g_slist_length (mon->wait_list)));

	if (mon->wait_list != NULL) {
		LOCK_DEBUG (g_message ("%s: (%d) signalling and dequeuing handle %p", __func__, GetCurrentThreadId (), mon->wait_list->data));

		SetEvent (mon->wait_list->data);
		mon->wait_list = g_slist_remove (mon->wait_list, mon->wait_list->data);
	}
}
