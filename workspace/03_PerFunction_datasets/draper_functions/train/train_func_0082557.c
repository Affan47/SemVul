remove_and_abort_threads (gpointer key, gpointer value, gpointer user)
{
	struct wait_data *wait=(struct wait_data *)user;
	MonoNativeThreadId self = mono_native_thread_id_get ();
	MonoInternalThread *thread = (MonoInternalThread *)value;
	HANDLE handle;

	if (wait->num >= MAXIMUM_WAIT_OBJECTS)
		return FALSE;


	if (!mono_native_thread_id_equals (thread_get_tid (thread), self)
	     && (thread->state & ThreadState_Background) != 0
	     && (thread->flags & MONO_THREAD_FLAG_DONT_MANAGE) == 0
	) {
		handle = mono_threads_open_thread_handle (thread->handle, thread_get_tid (thread));
		if (handle == NULL)
			return FALSE;


		wait->handles[wait->num]=thread->handle;
		wait->threads[wait->num]=thread;
		wait->num++;

		THREAD_DEBUG (g_print ("%s: Aborting id: %"G_GSIZE_FORMAT"\n", __func__, (gsize)thread->tid));
		mono_thread_internal_stop (thread);
		return TRUE;
	}

	return !mono_native_thread_id_equals (thread_get_tid (thread), self)
	        && !mono_gc_is_finalizer_internal_thread (thread);
}
