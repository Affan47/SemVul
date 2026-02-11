au_suite_fail_report(autounit_suite_t *tc)
{
  GSList* tmp;
  gint test_num;
  autounit_test_t* test;

  au_log_start("au_suite_fail_report");
  tmp = tc->tests;
  test_num = 0;
  g_print(_("FAIL %d of %d %s %f s (%ld us) total elapsed time\n"),
          tc->failed_tests, tc->total_tests,
          tc->suite_name->str,
	  tc->suite_seconds_elapsed, tc->suite_useconds_elapsed);
  while (tmp != NULL)
   {
     test = (autounit_test_t*)tmp->data;
     if (strlen(test->test_status->str)) {
       g_print(_("%s: elapsed time %f s (%ld us):failed assertions (%d of %d):\n"),
               test->test_name->str,
	       test->test_seconds_elapsed,
	       test->test_useconds_elapsed,
               test->failed_assertions, test->total_assertions);
       g_print("%s",test->test_status->str);
     }
     tmp = g_slist_next(tmp);
   }
  au_log_end("au_suite_fail_report");
}
