ccache_main(int argc, char *argv[])
{
	int c;
	size_t v;

	while ((c = getopt(argc, argv, "hszcCF:M:V")) != -1) {
		switch (c) {
		case 'V':
			printf("%s version %s\n", MYNAME, CCACHE_VERSION);
			printf("Copyright Andrew Tridgell 2002\n");
			printf("Released under the GNU GPL v2 or later\n");
			exit(0);

		case 'h':
			usage();
			exit(0);

		case 's':
			check_cache_dir();
			stats_summary();
			break;

		case 'c':
			check_cache_dir();
			cleanup_all(cache_dir);
			printf("Cleaned cache\n");
			break;

		case 'C':
			check_cache_dir();
			wipe_all(cache_dir);
			printf("Cleared cache\n");
			break;

		case 'z':
			check_cache_dir();
			stats_zero();
			printf("Statistics cleared\n");
			break;

		case 'F':
			check_cache_dir();
			v = atoi(optarg);
			if (stats_set_limits(v, -1) == 0) {
				printf("Set cache file limit to %u\n", (unsigned)v);
			} else {
				printf("Could not set cache file limit.\n");
				exit(1);
			}
			break;

		case 'M':
			check_cache_dir();
			v = value_units(optarg);
			if (stats_set_limits(-1, v) == 0) {
				printf("Set cache size limit to %uk\n", (unsigned)v);
			} else {
				printf("Could not set cache size limit.\n");
				exit(1);
			}
			break;

		default:
			usage();
			exit(1);
		}
	}

	return 0;
}
