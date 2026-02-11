my_timer_init_ext(void)
{
  int rc;
  sigset_t set, old_set;

  if (sigfillset(&set))
    return -1;


  if (pthread_sigmask(SIG_BLOCK, &set, &old_set))
    return -1;


  rc= start_helper_thread();


  pthread_sigmask(SIG_SETMASK, &old_set, NULL);

  return rc;
}
