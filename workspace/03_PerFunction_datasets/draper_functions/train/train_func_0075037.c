proactor_end_event_loop (void)
{
  ACE_TRACE ("ACE_Proactor::proactor_end_event_loop");

  int how_many = 0;

  {


    ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, mutex_, -1));


    this->end_event_loop_ = 1;


    how_many = this->event_loop_thread_count_;
    if (how_many == 0)
      return 0;
  }


  return this->proactor_post_wakeup_completions (how_many);
}
