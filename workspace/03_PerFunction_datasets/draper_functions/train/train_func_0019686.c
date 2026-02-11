thr_state (ACE_thread_t id,
                               ACE_UINT32& state)
{
  ACE_TRACE ("ACE_Thread_Manager::thr_state");
  ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, this->lock_, -1));

  int const self_check = ACE_OS::thr_equal (id, ACE_OS::thr_self ());


  if (self_check)
    {
      ACE_Thread_Descriptor *desc = ACE_LOG_MSG->thr_desc ();

      if (desc == 0)
        {
          return 0;
        }

      state = desc->thr_state_;
    }
  else
    {

      ACE_FIND (this->find_thread (id), ptr);

      if (ptr == 0)
        {
          return 0;
        }

      state = ptr->thr_state_;
    }

  return 1;
}
