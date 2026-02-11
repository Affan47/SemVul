__pthread_cond_timedwait_2_0 (cond, mutex, abstime)
     pthread_cond_2_0_t *cond;
     pthread_mutex_t *mutex;
     const struct timespec *abstime;
{
  if (cond->cond == NULL)
    {
      pthread_cond_t *newcond;

#if LLL_LOCK_INITIALIZER == 0
      newcond = (pthread_cond_t *) calloc (sizeof (pthread_cond_t), 1);
      if (newcond == NULL)
	return ENOMEM;
#else
      newcond = (pthread_cond_t *) malloc (sizeof (pthread_cond_t));
      if (newcond == NULL)
	return ENOMEM;


      (void) pthread_cond_init (newcond, NULL);
#endif

      if (atomic_compare_and_exchange_bool_acq (&cond->cond, newcond, NULL))

	free (newcond);
    }

  return __pthread_cond_timedwait (cond->cond, mutex, abstime);
}
