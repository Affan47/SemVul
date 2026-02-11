mono_thread_create_internal (MonoDomain *domain, gpointer func, gpointer arg, gboolean threadpool_thread, gboolean no_detach, guint32 stack_size)
{
	MonoThread *thread;
	MonoInternalThread *internal;
	StartInfo *start_info;
	gboolean res;

	thread = create_thread_object (domain);
	internal = create_internal_thread ();
	MONO_OBJECT_SETREF (thread, internal_thread, internal);

	start_info = g_new0 (StartInfo, 1);
	start_info->func = func;
	start_info->obj = thread;
	start_info->start_arg = arg;

	res = create_thread (thread, internal, start_info, threadpool_thread, no_detach, stack_size, TRUE);
	if (!res)
		return NULL;


	if (mono_check_corlib_version () == NULL)
		g_assert (((char*)&internal->unused2 - (char*)internal) == mono_defaults.internal_thread_class->fields [mono_defaults.internal_thread_class->field.count - 1].offset);

	return internal;
}
