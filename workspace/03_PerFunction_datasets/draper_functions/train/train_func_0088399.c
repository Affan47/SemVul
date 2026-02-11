main(int argc, char *argv[])
{
	const char *usage = "usage: test_pictures path_prefix\n";

	if(argc > 1 && 0 == strcmp(argv[1], "-h")) {
		puts(usage);
		return 0;
	}

	if(argc != 2) {
		fputs(usage, stderr);
		return 255;
	}

	return do_picture(argv[1])? 0 : 1;
}
