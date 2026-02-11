search_for_theme_or_die_trying (gchar *actual, gchar **rc_file)
{
	if (!is_themedir(actual, rc_file) &&
		!install_tarball(actual, rc_file) &&
		!is_installed_theme(actual, rc_file))
	{
		fprintf (stderr, "\
%s: Sorry, \"%s\" does not appear to be a valid theme directory or tarball!\n", execname, actual);
		exit (EXIT_FAILURE);
	}
}
