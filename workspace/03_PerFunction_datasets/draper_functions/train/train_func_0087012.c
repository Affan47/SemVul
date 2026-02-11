__gai_notify_only (struct sigevent *sigev, pid_t caller_pid)
{
  int result = 0;


  if (sigev->sigev_notify == SIGEV_THREAD)
    {

      pthread_t tid;
      pthread_attr_t attr, *pattr;

      pattr = (pthread_attr_t *) sigev->sigev_notify_attributes;
      if (pattr == NULL)
	{
	  pthread_attr_init (&attr);
	  pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
	  pattr = &attr;
	}


      struct notify_func *nf = malloc (sizeof *nf);
      if (nf == NULL)
	result = -1;
      else
	{
	  nf->func = sigev->sigev_notify_function;
	  nf->value = sigev->sigev_value;
	  if (pthread_create (&tid, pattr, notify_func_wrapper, nf) < 0)
	    {
	      free (nf);
	      result = -1;
	    }
	}
    }
  else if (sigev->sigev_notify == SIGEV_SIGNAL)

    if (__gai_sigqueue (sigev->sigev_signo, sigev->sigev_value, caller_pid)
	< 0)
      result = -1;

  return result;
}
