icall_cancel_blocking_socket_operation (MonoThread *thread)
{
	MonoInternalThread *internal;

	internal = thread->internal_thread;
	g_assert (internal);

	mono_thread_info_abort_socket_syscall_for_close (MONO_UINT_TO_NATIVE_THREAD_ID (internal->tid));
}
