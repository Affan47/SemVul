pw_pr_w_del_thread (void *arg)
{
	int i, idx = 1000 * GPOINTER_TO_INT (arg);

	mono_thread_info_attach ((gpointer)&arg);

	for (i = idx; i < idx + 1000; i++) {
		mono_os_mutex_lock (&global_mutex);
		mono_conc_hashtable_remove (hash, GINT_TO_POINTER (i + 1));
		mono_os_mutex_unlock (&global_mutex);
	}
	return NULL;
}
