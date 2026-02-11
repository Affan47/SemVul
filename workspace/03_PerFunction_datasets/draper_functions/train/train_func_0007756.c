tests_set (GstTest * test)
{
  guint i;

  for (i = 0; i < TESTS_COUNT; i++) {
    g_assert (test->tests[i] == NULL);
    test->tests[i] = tests[i].new (&tests[i]);
  }
}
