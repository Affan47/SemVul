__thread_mutex_unlock(pthread_mutex_t*mutex,_pthread_descr this) {
  if (mutex->owner==this) {
    if (mutex->kind==PTHREAD_MUTEX_RECURSIVE_NP) {
      if (--(mutex->count)) return 0;
    }
    mutex->owner=0;
    UNLOCK(mutex);
  }
  else if (mutex->kind==PTHREAD_MUTEX_ERRORCHECK_NP) {
    return EPERM;
  }
  return 0;
}
