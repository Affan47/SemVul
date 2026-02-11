save_ps_display_args(int argc, char **argv)
{
	save_argc = argc;
	save_argv = argv;

#if defined(PS_USE_CLOBBER_ARGV)


	{
		char	   *end_of_area = NULL;
		char	  **new_environ;
		int			i;


		for (i = 0; i < argc; i++)
		{
			if (i == 0 || end_of_area + 1 == argv[i])
				end_of_area = argv[i] + strlen(argv[i]);
		}

		if (end_of_area == NULL)
		{
			ps_buffer = NULL;
			ps_buffer_size = 0;
			return argv;
		}


		for (i = 0; environ[i] != NULL; i++)
		{
			if (end_of_area + 1 == environ[i])
				end_of_area = environ[i] + strlen(environ[i]);
		}

		ps_buffer = argv[0];
		last_status_len = ps_buffer_size = end_of_area - argv[0];


		new_environ = (char **) malloc((i + 1) * sizeof(char *));
		for (i = 0; environ[i] != NULL; i++)
			new_environ[i] = strdup(environ[i]);
		new_environ[i] = NULL;
		environ = new_environ;
	}
#endif

#if defined(PS_USE_CHANGE_ARGV) || defined(PS_USE_CLOBBER_ARGV)


	{
		char	  **new_argv;
		int			i;

		new_argv = (char **) malloc((argc + 1) * sizeof(char *));
		for (i = 0; i < argc; i++)
			new_argv[i] = strdup(argv[i]);
		new_argv[argc] = NULL;

#if defined(__darwin__)


		*_NSGetArgv() = new_argv;
#endif

		argv = new_argv;
	}
#endif

	return argv;
}
