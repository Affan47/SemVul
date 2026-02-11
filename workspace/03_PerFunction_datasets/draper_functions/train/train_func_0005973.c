cob_init (int argc, char **argv)
{
	char	*s;
	size_t	i;
	char	buff[32];

	if (!cob_initialized) {
		cob_set_signal ();

		cob_argc = argc;
		cob_argv = argv;


		runtime_err_str = cob_malloc (COB_ERRBUF_SIZE);

#ifdef	HAVE_SETLOCALE
		setlocale (LC_ALL, "");
		setlocale (LC_NUMERIC, "C");
		s = setlocale (LC_ALL, NULL);
		if (s) {
			locale_save = strdup (s);
		}
#endif
#ifdef	ENABLE_NLS
		bindtextdomain (PACKAGE, LOCALEDIR);
		textdomain (PACKAGE);
#endif


#if defined(_WIN32) && !defined(_MSC_VER)
		_setmode (_fileno (stdin), _O_BINARY);
		_setmode (_fileno (stdout), _O_BINARY);
		_setmode (_fileno (stderr), _O_BINARY);
#endif

		cob_init_numeric ();
		cob_init_strings ();
		cob_init_move ();
		cob_init_intrinsic ();
		cob_init_fileio ();
		cob_init_termio ();
		cob_init_call ();

		for (i = 0; i < 8; ++i) {
			memset (buff, 0, sizeof (buff));
			snprintf (buff, 31, "COB_SWITCH_%d", (int)(i + 1));
			s = getenv (buff);
			if (s && strcasecmp (s, "ON") == 0) {
				cob_switch[i] = 1;
			} else {
				cob_switch[i] = 0;
			}
		}

		s = getenv ("COB_LINE_TRACE");
		if (s && (*s == 'Y' || *s == 'y')) {
			cob_line_trace = 1;
		}

		cob_initialized = 1;
	}
}
