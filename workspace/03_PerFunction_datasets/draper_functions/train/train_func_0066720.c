PrintFailedTests(const UnitTest& unit_test) {
  const int failed_test_count = unit_test.failed_test_count();
  if (failed_test_count == 0) {
    return;
  }

  for (int i = 0; i < unit_test.total_test_case_count(); ++i) {
    const TestCase& test_case = *unit_test.GetTestCase(i);
    if (!test_case.should_run() || (test_case.failed_test_count() == 0)) {
      continue;
    }
    for (int j = 0; j < test_case.total_test_count(); ++j) {
      const TestInfo& test_info = *test_case.GetTestInfo(j);
      if (!test_info.should_run() || test_info.result()->Passed()) {
        continue;
      }
      ColoredPrintf(COLOR_RED, "[  FAILED  ] ");
      printf("%s.%s", test_case.name(), test_info.name());
      if (test_case.comment()[0] != '\0' ||
          test_info.comment()[0] != '\0') {
        printf(", where %s", test_case.comment());
        if (test_case.comment()[0] != '\0' &&
            test_info.comment()[0] != '\0') {
          printf(" and ");
        }
      }
      printf("%s\n", test_info.comment());
    }
  }
}
