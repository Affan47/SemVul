semaphore_up_(Semaphore * s,
		  const char * filename,
		  const int linenumber) {
  int value_after_op;
  pthread_cond_t * cond;

  cond = s->cond;
  MUTEX_LOCK(&(s->mutex));
  (s->v)++;
  value_after_op = s->v;
  GNUNET_ASSERT(0 == pthread_cond_signal(cond));
  MUTEX_UNLOCK(&(s->mutex));
  return value_after_op;
}
