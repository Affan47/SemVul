main(int argc, char *argv[])
{
	struct builtin_cmd *cmd;

	program = basename(argv[0]);

	if (argc < 2)
		usage();

	cmd = parse_builtin_cmd(argc, argv);
	if (!cmd)
		usage();

	return cmd->cmd_fn(argc, argv);
}
