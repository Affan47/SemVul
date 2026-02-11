mono_thread_pool_init (void)
{
	gint threads_per_cpu = 1;
	gint thread_count;
	gint cpu_count = mono_cpu_count ();
	int result;

	if (tp_inited == 2)
		return;

	result = InterlockedCompareExchange (&tp_inited, 1, 0);
	if (result == 1) {
		while (1) {
			SleepEx (1, FALSE);
			if (tp_inited == 2)
				return;
		}
	}

	MONO_GC_REGISTER_ROOT_FIXED (socket_io_data.sock_to_state);
	InitializeCriticalSection (&socket_io_data.io_lock);
	if (g_getenv ("MONO_THREADS_PER_CPU") != NULL) {
		threads_per_cpu = atoi (g_getenv ("MONO_THREADS_PER_CPU"));
		if (threads_per_cpu < 1)
			threads_per_cpu = 1;
	}

	thread_count = MIN (cpu_count * threads_per_cpu, 100 * cpu_count);
	threadpool_init (&async_tp, thread_count, MAX (100 * cpu_count, thread_count), async_invoke_thread);
	threadpool_init (&async_io_tp, cpu_count * 2, cpu_count * 4, async_invoke_thread);
	async_io_tp.is_io = TRUE;

	async_call_klass = mono_class_from_name (mono_defaults.corlib, "System", "MonoAsyncCall");
	g_assert (async_call_klass);

	InitializeCriticalSection (&wsqs_lock);
	wsqs = g_ptr_array_sized_new (MAX (100 * cpu_count, thread_count));

#ifndef DISABLE_PERFCOUNTERS
	async_tp.pc_nitems = init_perf_counter ("Mono Threadpool", "Work Items Added");
	g_assert (async_tp.pc_nitems);

	async_io_tp.pc_nitems = init_perf_counter ("Mono Threadpool", "IO Work Items Added");
	g_assert (async_io_tp.pc_nitems);

	async_tp.pc_nthreads = init_perf_counter ("Mono Threadpool", "# of Threads");
	g_assert (async_tp.pc_nthreads);

	async_io_tp.pc_nthreads = init_perf_counter ("Mono Threadpool", "# of IO Threads");
	g_assert (async_io_tp.pc_nthreads);
#endif
	tp_inited = 2;
#ifdef DEBUG
	signal (SIGALRM, signal_handler);
	alarm (2);
#endif
}
