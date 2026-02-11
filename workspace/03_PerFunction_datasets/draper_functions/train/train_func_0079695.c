beoboot_load(int argc, char **argv, const char *buf, off_t UNUSED(len),
	struct kexec_info *info)
{
	struct beoboot_header bb_header;
	const char *command_line, *kernel, *initrd;

	int debug, real_mode_entry;
	int opt;
	int result;


	static const struct option options[] = {
		KEXEC_ARCH_OPTIONS
		{ "debug",		0, 0, OPT_DEBUG },
		{ "real-mode",		0, 0, OPT_REAL_MODE },
		{ 0, 			0, 0, 0 },
	};
	static const char short_options[] = KEXEC_ARCH_OPT_STR "";


	debug = 0;
	real_mode_entry = 0;
	while((opt = getopt_long(argc, argv, short_options, options, 0)) != -1) {
		switch(opt) {
		default:

			if (opt < OPT_ARCH_MAX) {
				break;
			}
		case '?':
			usage();
			return -1;
		case OPT_DEBUG:
			debug = 1;
			break;
		case OPT_REAL_MODE:
			real_mode_entry = 1;
			break;
		}
	}


	memcpy(&bb_header, buf, sizeof(bb_header));
	command_line   = buf + sizeof(bb_header);
	kernel         = command_line + bb_header.cmdline_size;
	initrd         = NULL;
	if (bb_header.flags & BEOBOOT_INITRD_PRESENT) {
		initrd = kernel + bb_header.kernel_size;
	}

	result = do_bzImage_load(info,
		kernel,        bb_header.kernel_size,
		command_line,  bb_header.cmdline_size,
		initrd,        bb_header.initrd_size,
		real_mode_entry, debug);

	return result;
}
