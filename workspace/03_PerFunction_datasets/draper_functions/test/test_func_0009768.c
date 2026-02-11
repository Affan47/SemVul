switch_gc (char* argv[], const char* target_gc)
{
	GString *path;

	if (!strcmp (mono_gc_get_gc_name (), target_gc)) {
		return;
	}

	path = g_string_new (argv [0]);


	if (strstr (argv [0], "-sgen"))
		g_string_truncate (path, path->len - 5);
	else if (strstr (argv [0], "-boehm"))
		g_string_truncate (path, path->len - 6);

	g_string_append_c (path, '-');
	g_string_append (path, target_gc);

#ifdef HAVE_EXECVP
	execvp (path->str, argv);
#else
	fprintf (stderr, "Error: --gc=<NAME> option not supported on this platform.\n");
#endif
}
