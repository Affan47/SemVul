test_au_char_assert_simple(char *testname)
{
  autounit_test_t *b_t;
  char *oddmessage;
  char *oddmessage2;
  char *oddmessage3;
  char *tmp;

  oddmessage = "SNTHEudA)R#$DT!THDEIT";
  oddmessage2 = "sntovwditne023rhdn";
  oddmessage3 = "vwo023n2tn3hd5yn";

  b_t = au_new_test(g_string_new("test_sample_test"),test_sample_test);
  au_asserteq_char(b_t, 'c', 'd', oddmessage);
  loc_assert(testname, b_t->failed_assertions == 1,
             "failed_assertions should be 1");
  loc_assert(testname, b_t->total_assertions == 1,
             "total_assertions should be 1");
  tmp = g_strdup_printf("%s: `%s' not == `%s'", oddmessage, "c", "d");
  loc_assert(testname, strstr(b_t->test_status->str, tmp) != 0,
             "oddmessage not found in test_status");
  g_free(tmp);

  au_asserteq_char(b_t, 'r', 'z', oddmessage2);
  loc_assert(testname, b_t->failed_assertions == 2,
             "failed_assertions should be 2");
  loc_assert(testname, b_t->total_assertions == 2,
             "total_assertions should be 2");
  tmp = g_strdup_printf("%s: `%s' not == `%s'", oddmessage, "c", "d");
  loc_assert(testname, strstr(b_t->test_status->str, tmp) != 0,
             "oddmessage not found in test_status");
  g_free(tmp);
  tmp = g_strdup_printf("%s: `%s' not == `%s'", oddmessage2, "r", "z");
  loc_assert(testname, strstr(b_t->test_status->str, tmp) != 0,
             "oddmessage2 not found in test_status");
  g_free(tmp);

  au_asserteq_char(b_t, 'a', 'a', oddmessage3);
  loc_assert(testname, b_t->failed_assertions == 2,
             "failed_assertions should be 2");
  loc_assert(testname, b_t->total_assertions == 3,
             "total_assertions should be 3");
  loc_assert(testname, strstr(b_t->test_status->str, oddmessage) != 0,
             "oddmessage not found in test_status");
  loc_assert(testname, strstr(b_t->test_status->str, oddmessage2) != 0,
             "oddmessage2 not found in test_status");
  loc_assert(testname, strstr(b_t->test_status->str, oddmessage3) == 0,
             "oddmessage3 found in test_status");

  au_delete_test(b_t);
  return TRUE;
}
