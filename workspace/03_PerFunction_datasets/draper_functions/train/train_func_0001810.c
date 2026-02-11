main(int argc, char **argv)
{
	if (argc >= 2) {
		int i;
		for (i = 1; i < argc; i++) {
			if(strcmp(argv[i], "--all-symbols") == 0)
				all_symbols = 1;
			else if (strcmp(argv[i], "--absolute-percpu") == 0)
				absolute_percpu = 1;
			else if (strncmp(argv[i], "--symbol-prefix=", 16) == 0) {
				char *p = &argv[i][16];

				if ((*p == '"' && *(p+2) == '"') || (*p == '\'' && *(p+2) == '\''))
					p++;
				symbol_prefix_char = *p;
			} else if (strncmp(argv[i], "--page-offset=", 14) == 0) {
				const char *p = &argv[i][14];
				kernel_start_addr = strtoull(p, NULL, 16);
			} else
				usage();
		}
	} else if (argc != 1)
		usage();

	read_map(stdin);
	if (absolute_percpu)
		make_percpus_absolute();
	sort_symbols();
	optimize_token_table();
	write_src();

	return 0;
}
