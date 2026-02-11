destroy_argv_list(void)
{
	argv_p arg;

	while (argv_vars) {
		arg = argv_vars;
		argv_vars = argv_vars->next;
		pkg_free(arg);
	}
}
