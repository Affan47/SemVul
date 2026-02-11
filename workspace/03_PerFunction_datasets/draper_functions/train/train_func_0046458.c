main(int argc, char **argv)
{
	const char *val;
	if (argc != 2) {
		usage(var_usage);
	}

	setup_git_directory();
	val = NULL;

	if (strcmp(argv[1], "-l") == 0) {
		git_config(show_config);
		list_vars();
		return 0;
	}
	git_config(git_default_config);
	val = read_var(argv[1]);
	if (!val)
		usage(var_usage);

	printf("%s\n", val);

	return 0;
}
