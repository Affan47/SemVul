CuSuiteDetails(CuSuite* testSuite, char **details) {
	int i;
	int failCount = 0;
    char *s = NULL;

	if (testSuite->failCount == 0)
        {
            int passCount = testSuite->count - testSuite->failCount;
            const char* testWord = passCount == 1 ? "test" : "tests";
            asprintf_or_die(&s, "OK (%d %s)\n", passCount, testWord);
            string_append(details, s);
            free(s);
        } else {
		if (testSuite->failCount == 1)
			string_append(details, "There was 1 failure:\n");
		else {
            asprintf_or_die(&s, "There were %d failures:\n",
                            testSuite->failCount);
            string_append(details, s);
            free(s);
        }
		for (i = 0 ; i < testSuite->count ; ++i) {
			CuTest* testCase = testSuite->list[i];
			if (testCase->failed) {
				failCount++;
				asprintf_or_die(&s, "%d) %s:\n%s\n",
                         failCount, testCase->name, testCase->message);
                string_append(details, s);
                free(s);
			}
		}
		string_append(details, "\n!!!FAILURES!!!\n");

		asprintf_or_die(&s, "Runs: %d ",   testSuite->count);
        string_append(details, s);
        free(s);

        asprintf_or_die(&s, "Passes: %d ",
                        testSuite->count - testSuite->failCount);
        string_append(details, s);
        free(s);

		asprintf_or_die(&s, "Fails: %d\n",  testSuite->failCount);
        string_append(details, s);
        free(s);
	}
}
