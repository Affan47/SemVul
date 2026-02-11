thr_self (ACE_hthread_t &self)
{
  ACE_TRACE ("ACE_Thread_Manager::thr_self");

  ACE_Thread_Descriptor *desc =
    this->thread_desc_self ();

  if (desc == 0)
    return -1;
  else
    desc->self (self);

  return 0;
}
