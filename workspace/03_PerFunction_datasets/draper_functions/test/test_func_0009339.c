verbose_print_argv(char **argv)
{
	if (!opt_verbose)
		return;

	fprintf(stderr, _("exec"));
	for (; *argv; argv++)
		fprintf(stderr, " %s", *argv);
	fprintf(stderr, "\n");
}
