parse_flag (const char *option, char *flag)
{
	if (!strcmp (flag, "y"))
		return TRUE;
	else if (!strcmp (flag, "n"))
		return FALSE;
	else {
		fprintf (stderr, "debugger-agent: The valid values for the '%s' option are 'y' and 'n'.\n", option);
		exit (1);
		return FALSE;
	}
}
