main(int argc, char *argv[])
{
	struct table t;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <authfile>\n", argv[0]);
		exit(1);
	}
	table_init(&t);
	if (parser_auth(&t, argv[1])) {
		fprintf(stderr, "Failed to parse file %s\n", argv[1]);
		return -1;
	}
	table_print(&t);
	return 0;
}
