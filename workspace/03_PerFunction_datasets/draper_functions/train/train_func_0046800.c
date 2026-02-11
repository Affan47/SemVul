e2_command_run_at (gchar *command, const gchar *workdir, E2_CommandRange range)
{


	if ((command == NULL) || (*command == '\0'))
		return 1;
	g_strchug (command);
	if (*command == '\0')
		return 1;
	printd (DEBUG, "e2_command_run_at (command:%s,range:%d)", command, range);


	if (strchr (command, ';') == NULL)

		return _e2_command_run_single (command, workdir, range);

	gchar *s = command;
	gboolean run_in_shell = FALSE, done = FALSE;
	while (*s != '\0')
	{
		switch (*s++)
		{
			case ' ':
			case '\t':
			case '!':
			case '|':
				break;
			case '>':
				if (*s == '>')
					run_in_shell = TRUE;
			default:
				done = TRUE;
				break;
		}
		if (done)
			break;
	}
	if (run_in_shell)
		return _e2_command_run_single (command, workdir, range);

	gint result = 0;
	gchar *p;
	s = command;
	while ((p = e2_utils_bare_strchr (s, ';')) != NULL)
	{

		*p = '\0';
		result = _e2_command_run_single (s, workdir, range);
		s = p; s++;
		if (*s == '\0')
			return result;
	}

	return (_e2_command_run_single (s, workdir, range));
}
