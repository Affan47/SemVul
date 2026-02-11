initialize(LIBCWD_TSD_PARAM)
{
  bool initialized;
#if LIBCWD_THREAD_SAFE
  pthread_mutex_lock(&S_mutex);
#endif
  initialized = M_initialized;
  M_initialized = true;
#if LIBCWD_THREAD_SAFE
  pthread_mutex_unlock(&S_mutex);
#endif
  if (initialized)
    return;
#if LIBCWD_THREAD_SAFE
  pthread_mutexattr_t mutex_attr;
  pthread_mutexattr_init(&mutex_attr);
#if CWDEBUG_DEBUGT
  pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_ERRORCHECK);
#else
  pthread_mutexattr_settype(&mutex_attr, PTHREAD_MUTEX_NORMAL);
#endif
  pthread_mutex_init(&M_mutex, &mutex_attr);
  pthread_mutexattr_destroy(&mutex_attr);
#endif
  for (int i = 0; i < bucket_sizes; ++i)
  {
    M_count[i] = 0;
    M_keep[i] = 1;
    M_list_notfull[i].initialize(&M_count[i], (__libcwd_tsd.internal > 0) ? 1 : 0);
    M_list_full[i].initialize(&M_count[i], (__libcwd_tsd.internal > 0) ? 1 : 0);
  }
}
