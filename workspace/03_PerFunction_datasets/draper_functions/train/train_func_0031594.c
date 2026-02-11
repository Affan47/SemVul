proactor_event_loop_done (void)
{
  ACE_TRACE ("ACE_Proactor::proactor_event_loop_done");

  ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, mutex_, -1));

  return this->end_event_loop_ != 0 ? 1 : 0 ;
}
