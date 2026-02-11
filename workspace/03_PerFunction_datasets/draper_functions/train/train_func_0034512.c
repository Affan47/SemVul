au_run_test_child(autounit_test_t *t)
{
  GTimer *elapsed_timer;

  elapsed_timer = g_timer_new();
  {
    autounit_test_fp_t su_fn = (autounit_test_setup_fp_t) t->suite->setup_fp;
    autounit_test_fp_t fn = (autounit_test_fp_t) t->test_fp;
    autounit_test_fp_t td_fn = (autounit_test_teardown_fp_t) t->suite->teardown_fp;
    if (su_fn) su_fn(t);
    fn(t);
    if (td_fn) td_fn(t);
  }
  g_timer_stop(elapsed_timer);
  t->test_seconds_elapsed = g_timer_elapsed(elapsed_timer,
					    &t->test_useconds_elapsed);
  t->test_run = TRUE;
  g_timer_destroy(elapsed_timer);
}
