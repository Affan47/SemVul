print_details(git_testsuite *ts)
{
	int i;
	int failCount = 0;

	if (ts->fail_count == 0) {
		const char *testWord = ts->count == 1 ? "test" : "tests";
		printf("OK (%d %s)\n", ts->count, testWord);
	} else {
		printf("Failed (%d failures):\n", ts->fail_count);

		for (i = 0 ; i < ts->count ; ++i) {
			git_test *tc = ts->list[i];
			if (tc->failed) {
				failCount++;
				printf("  %d) \"%s\" [test %s @ %s]\n\t%s\n",
					failCount, tc->description, tc->name, tc->failed_pos, tc->message);
			}
		}
	}
}
