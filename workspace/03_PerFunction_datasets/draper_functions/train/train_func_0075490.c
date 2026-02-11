au_remove_test(autounit_suite_t *tc, autounit_test_t *t)
{

  if (tc->tests != NULL) {
    tc->tests = g_slist_remove(tc->tests,t);
    tc->total_tests--;
    au_test_unref(t);
  }
}
