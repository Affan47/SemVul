eject_main(int argc UNUSED_PARAM, char **argv)
{
	unsigned flags;
	const char *device;

	opt_complementary = "?1:t--T:T--t";
	flags = getopt32(argv, "tT" IF_FEATURE_EJECT_SCSI("s"));
	device = argv[optind] ? argv[optind] : "/dev/cdrom";


	xmove_fd(xopen_nonblocking(device), dev_fd);

	if (ENABLE_FEATURE_EJECT_SCSI && (flags & FLAG_SCSI))
		eject_scsi(device);
	else
		eject_cdrom(flags, device);

	if (ENABLE_FEATURE_CLEAN_UP)
		close(dev_fd);

	return EXIT_SUCCESS;
}
