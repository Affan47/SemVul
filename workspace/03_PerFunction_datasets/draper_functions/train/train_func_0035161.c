run_command(struct cmd_struct *p, int argc, const char **argv)
{
	int status;
	struct stat st;
	const char *prefix;

	prefix = NULL;
	if (p->option & RUN_SETUP)
		prefix = setup_git_directory();

	if (use_pager == -1 && p->option & RUN_SETUP)
		use_pager = check_pager_config(p->cmd);
	if (use_pager == -1 && p->option & USE_PAGER)
		use_pager = 1;
	commit_pager_choice();

	if (p->option & NEED_WORK_TREE)
		setup_work_tree();

	trace_argv_printf(argv, "trace: built-in: git");

	status = p->fn(argc, argv, prefix);
	if (status)
		return status & 0xff;


	if (fstat(fileno(stdout), &st))
		return 0;

	if (S_ISFIFO(st.st_mode) || S_ISSOCK(st.st_mode))
		return 0;


	if (fflush(stdout))
		die("write failure on standard output: %s", strerror(errno));
	if (ferror(stdout))
		die("unknown write failure on standard output");
	if (fclose(stdout))
		die("close failed on standard output: %s", strerror(errno));
	return 0;
}
