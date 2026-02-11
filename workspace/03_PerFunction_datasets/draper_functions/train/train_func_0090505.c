idle_start_test1_thread (gpointer use_thread_context)
{
	guint64 time;
	GThread *thread;

	g_mutex_lock (&test1_mutex);
	thread = g_thread_new ("test1_thread", test1_thread, use_thread_context);

	time = g_get_monotonic_time () + 5000000;
	if (g_cond_wait_until (&test1_cond, &test1_mutex, time))
		g_thread_join (thread);
	else {
		debug_printf (1, "  timeout!\n");
		g_thread_unref (thread);
		errors++;
	}

	g_mutex_unlock (&test1_mutex);
	g_main_loop_quit (test1_loop);
	return FALSE;
}
