on_proc_exit(pg_on_exit_callback function, Datum arg)
{
	if (on_proc_exit_index >= MAX_ON_EXITS)
		ereport(FATAL,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg_internal("out of on_proc_exit slots")));

	on_proc_exit_list[on_proc_exit_index].function = function;
	on_proc_exit_list[on_proc_exit_index].arg = arg;

	++on_proc_exit_index;

	if (!atexit_callback_setup)
	{
#ifdef HAVE_ATEXIT
		atexit(atexit_callback);
#else
		on_exit(atexit_callback, NULL);
#endif
		atexit_callback_setup = true;
	}
}
