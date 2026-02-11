pthread_tryjoin_np (threadid, thread_return)
     pthread_t threadid;
     void **thread_return;
{
  struct pthread *self;
  struct pthread *pd = (struct pthread *) threadid;


  if (DEBUGGING_P && __find_in_stack_list (pd) == NULL)

    return ESRCH;


  if (IS_DETACHED (pd))

    return EINVAL;

  self = THREAD_SELF;
  if (pd == self || self->joinid == pd)


    return EDEADLK;


  if (pd->tid != 0)
    return EBUSY;


  if (atomic_compare_and_exchange_bool_acq (&pd->joinid, self, NULL))

    return EINVAL;


  if (thread_return != NULL)
    *thread_return = pd->result;


  __free_tcb (pd);

  return 0;
}
