print_help(char *s)
{
	gint i;

	printf("Usage: %s [OPTION]... [TESTGROUP]...\n\n", s);
	printf("OPTIONS are:\n");
	printf("  -h, --help          show this help\n");
	printf("  -t, --time          time the tests\n");
	printf("  -i, --iterations    number of times to run tests\n");
	printf("  -q, --quiet         do not print test results; "
		"final time always prints\n");
	printf("  -n, --no-labels     print final time without labels, "
		"nice for scripts\n");
	printf("  -d, --debug         do not run tests, "
		"debug the driver itself for valgrind\n\n");
	printf("TESTGROUPS available:\n");

	for(i = 0; test_groups[i].name != NULL; i++) {
		if(test_groups[i].handler != fake_tests_init) {
			printf("  %s\n", test_groups[i].name);
		}
	}

	printf("\n");
}
