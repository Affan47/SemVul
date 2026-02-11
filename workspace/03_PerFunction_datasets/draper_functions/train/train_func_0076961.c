Pthread_mutex_lock(const char *caller, pthread_mutex_t *mutex)
{
  int status;

  if ( PTHREAD_Debug ) Message("+%s (mutex = %p)", __func__, (void *) mutex);

  status = pthread_mutex_lock(mutex);
  if ( status != 0 )
    {
      switch (status)
	{
	case EINVAL:
	  Error("The mutex has not been properly initialized!");
	  break;
	case EDEADLK:
	  Error("The mutex is already locked by the calling thread!");
	  break;
	default:
	  Error("Status %d unknown!", status, (void *) mutex);
	  break;
	}
    }

  if ( PTHREAD_Debug ) Message("-%s (mutex = %p)", __func__, (void *) mutex);
}
