ut_resetTest(const char *testName) {
    Test	t = findTest(testName);

    if (0 == t) {
	if (0 != testName) {
	    return;
	}
	t = currentTest;
	if (0 == t) {
	    return;
	}
    }
    t->pass = -1;
}
