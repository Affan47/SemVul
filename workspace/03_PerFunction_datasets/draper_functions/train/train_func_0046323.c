shell_exec_command(struct gnutella_shell *sh, int argc, const char *argv[])
{
	char *cmd;

	shell_check(sh);
	g_assert(argv);
	g_assert(argc > 0);

	cmd = main_command_line();
	shell_write_line(sh, REPLY_READY, cmd);
	HFREE_NULL(cmd);

	return REPLY_READY;
}
