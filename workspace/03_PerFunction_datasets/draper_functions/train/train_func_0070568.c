help (void)
{
	char *		p;
	char **		pp;

	for (pp = help_text; *pp; pp++) {
		p = *pp;
		printf ("%s\n", p);
	}
#ifndef NDMOS_OPTION_NO_CONTROL_AGENT
	help_rules();
#endif
}
