Pthread_cond_wait(const char *caller, pthread_cond_t *cond, pthread_mutex_t *mutex)
{
  if ( PTHREAD_Debug ) Message("+%s (cond = %p, mutex =  %p)",
			       __func__, (void *) cond, (void *) mutex);

  pthread_cond_wait(cond, mutex);

  if ( PTHREAD_Debug ) Message("-%s (cond = %p, mutex = %p)",
			       __func__, (void *) cond, (void *) mutex);
}
