mono_profiler_load (const char *desc)
{
	char *cdesc = NULL;
	mono_gc_base_init ();

	if (!desc || (strcmp ("default", desc) == 0)) {
		desc = "log:report";
	}

	if (strncmp (desc, "default:", 8) == 0) {
		gchar **args, **ptr;
		GString *str = g_string_new ("log:report");
		args = g_strsplit (desc + 8, ",", -1);
		for (ptr = args; ptr && *ptr; ptr++) {
			const char *arg = *ptr;

			if (!strcmp (arg, "time"))
				g_string_append (str, ",calls");
			else if (!strcmp (arg, "alloc"))
				g_string_append (str, ",alloc");
			else if (!strcmp (arg, "stat"))
				g_string_append (str, ",sample");
			else if (!strcmp (arg, "jit"))
				continue;
			else if (strncmp (arg, "file=", 5) == 0) {
				g_string_append_printf (str, ",output=%s", arg + 5);
			} else {
				fprintf (stderr, "profiler : Unknown argument '%s'.\n", arg);
				return;
			}
		}
		desc = cdesc = g_string_free (str, FALSE);
	}
	{
		const char* col = strchr (desc, ':');
		char* libname;
		char *mname;
		gboolean res = FALSE;

		if (col != NULL) {
			mname = g_memdup (desc, col - desc + 1);
			mname [col - desc] = 0;
		} else {
			mname = g_strdup (desc);
		}
		if (!load_embedded_profiler (desc, mname)) {
			libname = g_strdup_printf ("mono-profiler-%s", mname);
			if (!load_profiler_from_directory (NULL, libname, desc)) {
				res = FALSE;
#if defined (MONO_ASSEMBLIES)
				res = load_profiler_from_directory (mono_assembly_getrootdir (), libname, desc);
#endif
				if (!res)
					g_warning ("The '%s' profiler wasn't found in the main executable nor could it be loaded from '%s'.", mname, libname);
			}
			g_free (libname);
		}
		g_free (mname);
	}
	g_free (cdesc);
}
