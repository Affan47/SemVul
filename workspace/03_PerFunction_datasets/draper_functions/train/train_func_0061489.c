do_close_filesys(int argc, char **argv)
{
	int	c;

	if (check_fs_open(argv[0]))
		return;

	reset_getopt();
	while ((c = getopt (argc, argv, "a")) != EOF) {
		switch (c) {
		case 'a':
			current_fs->flags &= ~EXT2_FLAG_MASTER_SB_ONLY;
			break;
		default:
			goto print_usage;
		}
	}

	if (argc > optind) {
	print_usage:
		com_err(0, 0, "Usage: close_filesys [-a]");
		return;
	}

	close_filesystem();
}
