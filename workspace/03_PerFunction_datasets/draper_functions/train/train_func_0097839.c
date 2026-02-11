open_uri(const gchar *uri, const gchar *cmdline)
{

#ifndef G_OS_WIN32
	gchar buf[BUFFSIZE];
	gchar *p;
	gchar encoded_uri[BUFFSIZE];
	cm_return_val_if_fail(uri != NULL, -1);


	encode_uri(encoded_uri, BUFFSIZE, uri);

	if (cmdline &&
	    (p = strchr(cmdline, '%')) && *(p + 1) == 's' &&
	    !strchr(p + 2, '%'))
		g_snprintf(buf, sizeof(buf), cmdline, encoded_uri);
	else {
		if (cmdline)
			g_warning("Open URI command-line is invalid "
				  "(there must be only one '%%s'): %s",
				  cmdline);
		g_snprintf(buf, sizeof(buf), DEFAULT_BROWSER_CMD, encoded_uri);
	}

	execute_command_line(buf, TRUE);
#else
	ShellExecute(NULL, "open", uri, NULL, NULL, SW_SHOW);
#endif
	return 0;
}
