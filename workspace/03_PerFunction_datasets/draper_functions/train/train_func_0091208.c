mountpoint_main(int argc UNUSED_PARAM, char **argv)
{
	struct stat st;
	const char *msg;
	char *arg;
	int rc, opt;

	opt_complementary = "=1";
	opt = getopt32(argv, "qdxn");
#define OPT_q (1)
#define OPT_d (2)
#define OPT_x (4)
#define OPT_n (8)
	arg = argv[optind];
	msg = "%s";

	rc = (opt & OPT_x) ? stat(arg, &st) : lstat(arg, &st);
	if (rc != 0)
		goto err;

	if (opt & OPT_x) {
		if (S_ISBLK(st.st_mode)) {
			printf("%u:%u\n", major(st.st_rdev),
						minor(st.st_rdev));
			return EXIT_SUCCESS;
		}
		errno = 0;
		msg = "%s: not a block device";
		goto err;
	}

	errno = ENOTDIR;
	if (S_ISDIR(st.st_mode)) {
		dev_t st_dev = st.st_dev;
		ino_t st_ino = st.st_ino;
		char *p = xasprintf("%s/..", arg);

		if (stat(p, &st) == 0) {

			int is_not_mnt = (st_dev == st.st_dev) && (st_ino != st.st_ino);

			if (opt & OPT_d)
				printf("%u:%u\n", major(st_dev), minor(st_dev));
			if (opt & OPT_n) {
				const char *d = find_block_device(arg);


				if (!d) {
					d = "UNKNOWN";


				}
				printf("%s %s\n", d, arg);
			}
			if (!(opt & (OPT_q | OPT_d | OPT_n)))
				printf("%s is %sa mountpoint\n", arg, is_not_mnt ? "not " : "");
			return is_not_mnt;
		}
		arg = p;

	}

 err:
	if (!(opt & OPT_q))
		bb_perror_msg(msg, arg);
	return EXIT_FAILURE;
}
