ut_false(bool condition) {
    if (condition) {
	ut_print("%s.%s Failed: Condition was true\n", group, currentTest->name);
	currentTest->pass = 0;
    } else if (0 != currentTest->pass) {
	currentTest->pass = 1;
    }
    return !condition;
}
