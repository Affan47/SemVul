parse_cmdline_and_init_file (int argc, TCHAR **argv)
{

	_tcscpy (optionsfile, _T(""));

#ifdef OPTIONS_IN_HOME
	{
		TCHAR *home = getenv ("HOME");
		if (home != NULL && strlen (home) < 240)
		{
			_tcscpy (optionsfile, home);
			_tcscat (optionsfile, _T("/"));
		}
	}
#endif

	parse_cmdline_2 (argc, argv);

	_tcscat (optionsfile, restart_config);

	if (! target_cfgfile_load (&currprefs, optionsfile, 0, default_config)) {
		write_log (_T("failed to load config '%s'\n"), optionsfile);
#ifdef OPTIONS_IN_HOME

		_tcscpy (optionsfile, restart_config);
		target_cfgfile_load (&currprefs, optionsfile, 0, default_config);
#endif
	}
	fixup_prefs (&currprefs);

	parse_cmdline (argc, argv);
}
