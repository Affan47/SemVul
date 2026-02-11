test_timer_no_tap(void)
{
  int rc, state;
  test_timer_t test;

  memset(&test, 0, sizeof(test_timer_t));

  pthread_mutex_init(&test.mutex, NULL);
  pthread_cond_init(&test.cond, NULL);

  test.timer.notify_function= timer_notify_function;

  rc= my_timer_create(&test.timer);
  assert(rc == 0);

  pthread_mutex_lock(&test.mutex);

  rc= my_timer_set(&test.timer, 5);
  assert(rc == 0);

  assert(test.fired == 0);

  while (!test.fired)
    pthread_cond_wait(&test.cond, &test.mutex);

  assert(test.fired == 1);

  rc= my_timer_reset(&test.timer, &state);
  assert(rc == 0);

  assert(state == 0);

  pthread_mutex_unlock(&test.mutex);

  pthread_mutex_destroy(&test.mutex);
  pthread_cond_destroy(&test.cond);
  my_timer_delete(&test.timer);
}
