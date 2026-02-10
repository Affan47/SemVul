simple_method_enter (MonoProfiler *prof, MonoMethod *method)
{
	static int guithread;
	static gboolean guithread_set = FALSE;
	MonoClass* klass;
	const char* name_space;

	klass = mono_method_get_class (method);
	name_space = mono_class_get_namespace (klass);

	int current_thread_id = (int) pthread_self();

	if (strstr (name_space, "Gtk") == name_space || strstr (name_space, "Gdk") == name_space) {
		const char* method_name = mono_method_get_name (method);
		const char* klass_name = mono_class_get_name (klass);

		if (!guithread_set && strcmp (klass_name, "Application")==0 && strcmp (method_name, "Init")==0) {
			guithread_set = TRUE;
			guithread = current_thread_id;
			printf ("*** GUI THREAD INITIALIZED: %u\n", guithread);
			fflush (NULL);
			return;
		}
		if (!guithread_set) {
			return;
		}
		if (current_thread_id != guithread &&
			!(strcmp (klass_name, "Object")==0 && strcmp (method_name, "Dispose")==0) &&
			!(strcmp (klass_name, "Widget")==0 && strcmp (method_name, "Dispose")==0) &&
			!(strcmp (klass_name, "Application")==0 && strcmp (method_name, "Invoke")==0) &&
			!(strcmp (method_name, "Finalize")==0) &&
			!(strcmp (method_name, "get_NativeDestroyHandler")==0) &&
			!(strcmp (method_name, "remove_InternalDestroyed")==0) &&
			!(strcmp (method_name, "remove_Destroyed")==0)
		) {
			printf ("*** GTK CALL NOT IN GUI THREAD: %s.%s\n", klass_name, method_name);
	        mono_stack_walk_no_il (stack_walk_fn, NULL);
			fflush (NULL);
		}
	}
}
