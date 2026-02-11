au_suite_gather_totals(autounit_suite_t *tc)
{


  GSList* tmp;
  autounit_test_t *test;

  au_log_start("au_suite_gather_totals");
  tmp = tc->tests;
  while (tmp != NULL)
    {
      test = (autounit_test_t*) tmp->data;
      tc->suite_seconds_elapsed += test->test_seconds_elapsed;
      tc->suite_useconds_elapsed += test->test_useconds_elapsed;
      if (test->failed_assertions > 0)
      {
          tc->failed_tests++;
      }
      tmp = g_slist_next(tmp);
   }
  au_log_end("au_suite_gather_totals");
}
