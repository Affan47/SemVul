proactor_run_event_loop (ACE_Time_Value &tv,
                                       PROACTOR_EVENT_HOOK eh)
{
  ACE_TRACE ("ACE_Proactor::proactor_run_event_loop");
  int result = 0;

  {
    ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, mutex_, -1));


    if (this->end_event_loop_ != 0
       || tv == ACE_Time_Value::zero)
      return 0;


    this->event_loop_thread_count_ ++;
  }


  for (;;)
    {


      if (this->end_event_loop_ != 0)
        break;


      result = this->handle_events (tv);

      if (eh != 0 && (*eh) (this))
        continue;

      if (result == -1 || result == 0)
        break;
    }


  {
    ACE_MT (ACE_GUARD_RETURN (ACE_Thread_Mutex, ace_mon, mutex_, -1));


    this->event_loop_thread_count_ --;

    if (this->event_loop_thread_count_ > 0
       && this->end_event_loop_ != 0)
       this->proactor_post_wakeup_completions (1);
  }

  return result;
}
