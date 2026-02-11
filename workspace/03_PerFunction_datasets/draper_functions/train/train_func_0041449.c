handle_events (ACE_Time_Value *max_wait_time)
{
  ACE_TRACE ("ACE_Dev_Poll_Reactor::handle_events");


  ACE_Countdown_Time countdown (max_wait_time);

  Token_Guard guard (this->token_);
  int const result = guard.acquire_quietly (max_wait_time);


  if (!guard.is_owner ())
    return result;

  if (this->deactivated_)
    return -1;


  ACE_MT (countdown.update ());

  return this->handle_events_i (max_wait_time, guard);
}
