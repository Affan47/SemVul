test_au_set_fork_mode(char *testname)
{
  autounit_test_t *b_t;
  b_t = au_new_test(g_string_new("test_sample_test"),test_sample_test);

  loc_assert(testname,  b_t->do_fork == TRUE,
             "default fork mode");
  au_test_set_fork_mode(b_t,FALSE);
  loc_assert(testname,  b_t->do_fork == FALSE,
             "changed fork mode (FALSE)");
  au_test_set_fork_mode(b_t,TRUE);
  loc_assert(testname,  b_t->do_fork == TRUE,
             "changed fork mode (TRUE)");

  au_delete_test(b_t);
  return TRUE;
}
