main(int argc, char **argv)
{
	char *p, *offset, *encryption, *passfd, *device, *file;
	int delete, find, c;
	int res = 0;
	int ro = 0;
	int pfd = -1;
	unsigned long long off;


	delete = find = 0;
	off = 0;
	offset = encryption = passfd = NULL;

	progname = argv[0];
	if ((p = strrchr(progname, '/')) != NULL)
		progname = p+1;

	while ((c = getopt(argc, argv, "de:E:fho:p:v")) != -1) {
		switch (c) {
		case 'd':
			delete = 1;
			break;
		case 'E':
		case 'e':
			encryption = optarg;
			break;
		case 'f':
			find = 1;
			break;
		case 'h':
			usage(stdout);
			break;
		case 'o':
			offset = optarg;
			break;
		case 'p':
			passfd = optarg;
			break;
		case 'v':
			verbose = 1;
			break;
		default:
			usage(stderr);
		}
	}

	if (argc == 1) {
		usage(stderr);
	} else if (delete) {
		if (argc != optind+1 || encryption || offset || find)
			usage(stderr);
	} else if (find) {
		if (argc < optind || argc > optind+1)
			usage(stderr);
	} else {
		if (argc < optind+1 || argc > optind+2)
			usage(stderr);
	}

	if (find) {
		device = find_unused_loop_device();
		if (device == NULL)
			return -1;
		if (verbose)
			printf("Loop device is %s\n", device);
		if (argc == optind) {
			printf("%s\n", device);
			return 0;
		}
		file = argv[optind];
	} else {
		device = argv[optind];
		if (argc == optind+1)
			file = NULL;
		else
			file = argv[optind+1];
	}

	if (delete)
		res = del_loop(device);
	else if (file == NULL)
		res = show_loop(device);
	else {
		if (offset && sscanf(offset, "%llu", &off) != 1)
			usage(stderr);
		if (passfd && sscanf(passfd, "%d", &pfd) != 1)
			usage(stderr);
		res = set_loop(device, file, off, encryption, pfd, &ro);
	}
	return res;
}
