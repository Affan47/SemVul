main(int argc, char **argv)
{
	int i;
	char *dir = NULL;

	argv++;
	for (i = 1; i < argc; i++) {
		char *arg = *argv++;

		if (*arg == '-') {

			usage(receive_pack_usage);
		}
		if (dir)
			usage(receive_pack_usage);
		dir = arg;
	}
	if (!dir)
		usage(receive_pack_usage);

	if (!enter_repo(dir, 0))
		die("'%s': unable to chdir or not a git archive", dir);

	if (is_repository_shallow())
		die("attempt to push into a shallow repository");

	git_config(receive_pack_config);

	if (0 <= transfer_unpack_limit)
		unpack_limit = transfer_unpack_limit;
	else if (0 <= receive_unpack_limit)
		unpack_limit = receive_unpack_limit;

	write_head_info();


	packet_flush(1);

	read_head_info();
	if (commands) {
		const char *unpack_status = NULL;

		if (!delete_only(commands))
			unpack_status = unpack();
		execute_commands(unpack_status);
		if (pack_lockfile)
			unlink(pack_lockfile);
		if (report_status)
			report(unpack_status);
		run_hook(post_receive_hook);
		run_update_post_hook(commands);
	}
	return 0;
}
