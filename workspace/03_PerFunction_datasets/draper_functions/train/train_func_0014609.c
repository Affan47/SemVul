mono_runtime_run_main (MonoMethod *method, int argc, char* argv[],
		       MonoObject **exc)
{
	int i;
	MonoArray *args = NULL;
	MonoDomain *domain = mono_domain_get ();
	gchar *utf8_fullpath;
	MonoMethodSignature *sig;

	g_assert (method != NULL);

	mono_thread_set_main (mono_thread_current ());

	main_args = g_new0 (char*, argc);
	num_main_args = argc;

	if (!g_path_is_absolute (argv [0])) {
		gchar *basename = g_path_get_basename (argv [0]);
		gchar *fullpath = g_build_filename (method->klass->image->assembly->basedir,
						    basename,
						    NULL);

		utf8_fullpath = mono_utf8_from_external (fullpath);
		if(utf8_fullpath == NULL) {


			g_print ("\nCannot determine the text encoding for the assembly location: %s\n", fullpath);
			g_print ("Please add the correct encoding to MONO_EXTERNAL_ENCODINGS and try again.\n");
			exit (-1);
		}

		g_free (fullpath);
		g_free (basename);
	} else {
		utf8_fullpath = mono_utf8_from_external (argv[0]);
		if(utf8_fullpath == NULL) {
			g_print ("\nCannot determine the text encoding for the assembly location: %s\n", argv[0]);
			g_print ("Please add the correct encoding to MONO_EXTERNAL_ENCODINGS and try again.\n");
			exit (-1);
		}
	}

	main_args [0] = utf8_fullpath;

	for (i = 1; i < argc; ++i) {
		gchar *utf8_arg;

		utf8_arg=mono_utf8_from_external (argv[i]);
		if(utf8_arg==NULL) {

			g_print ("\nCannot determine the text encoding for argument %d (%s).\n", i, argv[i]);
			g_print ("Please add the correct encoding to MONO_EXTERNAL_ENCODINGS and try again.\n");
			exit (-1);
		}

		main_args [i] = utf8_arg;
	}
	argc--;
	argv++;

	sig = mono_method_signature (method);
	if (!sig) {
		g_print ("Unable to load Main method.\n");
		exit (-1);
	}

	if (sig->param_count) {
		args = (MonoArray*)mono_array_new (domain, mono_defaults.string_class, argc);
		for (i = 0; i < argc; ++i) {


			gchar *str = mono_utf8_from_external (argv [i]);
			MonoString *arg = mono_string_new (domain, str);
			mono_array_setref (args, i, arg);
			g_free (str);
		}
	} else {
		args = (MonoArray*)mono_array_new (domain, mono_defaults.string_class, 0);
	}

	mono_assembly_set_main (method->klass->image->assembly);

	return mono_runtime_exec_main (method, args, exc);
}
