git_testsuite_run(git_testsuite *ts)
{
	int i, fail_count;

	printf("Suite \"%s\": ", ts->name);

	for (i = 0 ; i < ts->count ; ++i) {
		git_test *tc = ts->list[i];

		test_run(tc);
		if (tc->failed) {
			ts->fail_count++;
			putchar('F');
		} else
			putchar('.');
	}
	printf("\n  ");
	print_details(ts);
	fail_count = ts->fail_count;

	free_suite(ts);
	return fail_count;
}
