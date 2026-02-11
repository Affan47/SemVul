mLock(pthread_mutex_t *mutex)
{
  int err;

  if((err = pthread_mutex_lock(mutex)))
    return nerr_raise(NERR_LOCK, "Mutex lock failed: %s", strerror(err));

  return STATUS_OK;
}
