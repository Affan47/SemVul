mono_threads_abort_appdomain_threads (MonoDomain *domain, int timeout)
{
#ifdef __native_client__
	return FALSE;
#endif

	abort_appdomain_data user_data;
	guint32 start_time;
	int orig_timeout = timeout;
	int i;

	THREAD_DEBUG (g_message ("%s: starting abort", __func__));

	start_time = mono_msec_ticks ();
	do {
		mono_threads_lock ();

		user_data.domain = domain;
		user_data.wait.num = 0;

		mono_g_hash_table_foreach (threads, collect_appdomain_thread, &user_data);
		mono_threads_unlock ();

		if (user_data.wait.num > 0) {

			for (i = 0; i < user_data.wait.num; ++i)
				ves_icall_System_Threading_Thread_Abort (user_data.wait.threads [i], NULL);


			wait_for_tids (&user_data.wait, 100);
		}


		timeout -= mono_msec_ticks () - start_time;
		start_time = mono_msec_ticks ();

		if (orig_timeout != -1 && timeout < 0)
			return FALSE;
	}
	while (user_data.wait.num > 0);

	THREAD_DEBUG (g_message ("%s: abort done", __func__));

	return TRUE;
}
