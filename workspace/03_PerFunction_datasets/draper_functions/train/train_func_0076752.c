handle_max_heap_size(const char *arg)
{
	max_heap_size = parse_long(arg);

	if (!max_heap_size) {
		fprintf(stderr, "%s: unparseable heap size '%s'\n", program_name, arg);
		usage(stderr, EXIT_FAILURE);
	}
}
