mono_gdb_render_native_backtraces (pid_t crashed_pid)
{
	const char *argv [9];
	char template_ [] = "/tmp/mono-lldb-commands.XXXXXX";
	char buf1 [128];
	FILE *commands;
	gboolean using_lldb = FALSE;

	argv [0] = g_find_program_in_path ("gdb");
	if (argv [0] == NULL) {
		argv [0] = g_find_program_in_path ("lldb");
		using_lldb = TRUE;
	}

	if (argv [0] == NULL)
		return;

	if (using_lldb) {
		if (mkstemp (template_) == -1)
			return;

		commands = fopen (template_, "w");

		fprintf (commands, "process attach --pid %ld\n", (long) crashed_pid);
		fprintf (commands, "thread list\n");
		fprintf (commands, "thread backtrace all\n");
		fprintf (commands, "detach\n");
		fprintf (commands, "quit\n");

		fflush (commands);
		fclose (commands);

		argv [1] = "--source";
		argv [2] = template_;
		argv [3] = 0;
	} else {
		argv [1] = "-ex";
		sprintf (buf1, "attach %ld", (long) crashed_pid);
		argv [2] = buf1;
		argv [3] = "--ex";
		argv [4] = "info threads";
		argv [5] = "--ex";
		argv [6] = "thread apply all bt";
		argv [7] = "--batch";
		argv [8] = 0;
	}

	execv (argv [0], (char**)argv);

	if (using_lldb)
		unlink (template_);
}
